#include "country_vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "operation.h"

void free_repository(Repository* vec) {
    /*
    function to free the space after repository use
    Repository* vec: the repository to be freed
    */
    if (vec && get_countries(vec)) {
        free(get_countries(vec));
    }
}


Country* get_countries(const Repository* vec) {
    return vec->countries;
}

int get_vector_size(const Repository* vec) {
    return vec->size;
}

int get_vector_capacity(const Repository* vec) {
    return vec->capacity;
}

void set_countries(Repository* vec, Country* countries, int size) {
    vec->countries = countries;
    vec->size = size;
}

void set_vector_size(Repository* vec, int size) {
    vec->size = size;
}

void set_vector_capacity(Repository* vec, int capacity) {
    vec->capacity = capacity;
}

int init_vector(Repository* vec) {
    /*
    intializes a vector of countries which is dynamically allocated
    CountryVector* vec: the new vector of countries
    return: 0 if the vector is created, -1 if there was an error
    */
    if (!vec) return -1;

    set_vector_size(vec, 0);
    set_vector_capacity(vec, INITIAL_CAPACITY);
    set_countries(vec, (Country*)malloc(get_vector_capacity(vec) * sizeof(Country)), 0);

    if (get_countries(vec) == NULL) {
        return -1;
    }
    return 0;
}

int resize_vector(Repository* vec) {
    /*
    resizes the vector in case of insufficient memory
    CountryVector* vec: the vector of countries
    */

    set_vector_capacity(vec, get_vector_capacity(vec) * 2);
    set_countries(vec, (Country*)realloc(get_countries(vec), get_vector_capacity(vec) * sizeof(Country)), get_vector_size(vec));

    if (get_countries(vec) == NULL) {
        return -1;
    }
    return 0;
}

int add_country(Repository* vec, char* name, char* continent, int population) {
    /*
    adds a new country to the vector of countries
    CountryVector* vec: the vector
    char* name: the name of the country
    char* continent: it's continent
    int population: it's population in millions
    return: the state of the vector while trying to add
    */
    for (int i = 0; i < get_vector_size(vec); i++) {
        if (_stricmp(get_countries(vec)[i].name, name) == 0) {
            return 1;
        }
    }

    if (!is_valid_continent(continent)) {
        return 2;
    }

    if (get_vector_size(vec) == get_vector_capacity(vec)) {
        resize_vector(vec);
    }

    strcpy(get_countries(vec)[get_vector_size(vec)].name, name);
    strcpy(get_countries(vec)[get_vector_size(vec)].continent, continent);
    get_countries(vec)[get_vector_size(vec)].population = population;
    set_vector_size(vec, get_vector_size(vec) + 1);

    return 0;
}



int delete_country(Repository* vec, char* name) {
    /*
    deletes a country from the vector
    CountryVector* vec: the vector of countries
    char* name: name of the deleted country
    */
    int index = -1;
    for (int i = 0; i < get_vector_size(vec); i++) {
        if (_stricmp(get_countries(vec)[i].name, name) == 0) {
            index = i;
            for (int j = i; j < get_vector_size(vec) - 1; j++) {
                get_countries(vec)[j] = get_countries(vec)[j + 1];
            }
            set_vector_size(vec, get_vector_size(vec) - 1);
            break;
        }
    }
    if (index != -1) {
        return 0;
    }
    else {
        return 1;
    }
}



int update_country(Repository* vec, char* name, char* new_continent, int new_population) {
    /*
    changing a countries continent and/or population
    Repository* vec: the repository in which the data is saved
    char* name: the name of the country
    char* new_continent: the new continent name to be changed
    int new_population: the new population of that country
    return: the state of the change (2 for invalid data, 1 for country not existing and 0 for success
    */
    int index = -1;
    for (int i = 0; i < get_vector_size(vec); i++) {
        if (_stricmp(get_countries(vec)[i].name, name) == 0) {
            index = i;

            if (new_continent != NULL && strlen(new_continent) > 0) {
                if (!is_valid_continent(new_continent)) {
                    return 2;
                }
                strcpy(get_countries(vec)[i].continent, new_continent);
            }

            if (new_population >= 0) {
                get_countries(vec)[i].population = new_population;
            }

            break;
        }
    }

    if (index != -1) {
        return 0;
    }
    else {
        return 1;
    }
}



int migrate_population(Repository* vec, char* from, char* to, int people) {
    /*
    Migrate population from one country to another.
    Repository* vec: the repository in which the data is stored
    char* from: the country imigrateng from
    char* to: the country imingratin to (the name)
    int people: the population migrating in millions
    return: the state - 3 for not enough people to migrate
    */
    int from_index = -1, to_index = -1;

    for (int i = 0; i < get_vector_size(vec); i++) {
        if (_stricmp(get_countries(vec)[i].name, from) == 0) {
            from_index = i;
        }
        if (_stricmp(get_countries(vec)[i].name, to) == 0) {
            to_index = i;
        }
    }

    if (from_index == -1) {
        return 1;
    }
    if (to_index == -1) {
        return 2;
    }

    if (get_countries(vec)[from_index].population < people) {
        return 3;
    }

    get_countries(vec)[from_index].population -= people;
    get_countries(vec)[to_index].population += people;

    return 0;
}


Country* search_country(Repository* vec, char* query, int* result_count) {
    /*
    search a country with a given substring
    CountryVector* vec: the vector
    char* query: the substring
    int* result_count:the number of countries with that given string in their name
    return: the vector with those countries
    */
    *result_count = 0;

    Country* results = (Country*)malloc(vec->size * sizeof(Country));
    if (results == NULL) {
        return NULL;
    }

    for (int i = 0; i < vec->size; i++) {
        if (strstr(vec->countries[i].name, query) != NULL) {
            results[*result_count] = vec->countries[i];
            (*result_count)++;
        }
    }

    if (*result_count == 0) {
        free(results);
        return NULL;
    }

    results = (Country*)realloc(results, (*result_count) * sizeof(Country));
    if (results == NULL) {
        return NULL;
    }
    return results;
}



//Country* search_country(Repository* vec, char* query, int* result_count) {
    /*
    search a country with a given substring
    CountryVector* vec: the vector
    char* query: the substring
    int* result_count:the number of countries with that given string in their name
    return: the vector with those countries
    */
    /*
        *result_count = 0;

        Country* results = (Country*)malloc(vec->size * sizeof(Country));
        if (results == NULL) {
            return NULL;
        }

        for (int i = 0; i < vec->size; i++) {
            if (strstr(vec->countries[i].name, query) != NULL) {
                results[*result_count] = vec->countries[i];
                (*result_count)++;
            }
        }

        if (*result_count == 0) {
            free(results);
            return NULL;
        }
        results = (Country*)realloc(results, (*result_count) * sizeof(Country));
        return results;
    }*/



