#include "controller.h"
#include "country_vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Operation undoStack[100];
int undoTop = -1;
Operation redoStack[100];
int redoTop = -1;

void* create_service() {
    /*
    create a service at the start of the program
    return: the new service
    */
    Service* srv = (Service*)malloc(sizeof(Service));
    if (!srv) {
        exit(1);
    }
    srv->repo = (Repository*)malloc(sizeof(Repository));
    if (!srv->repo) {
        free(srv);
        exit(1);
    }
    init_vector(srv->repo);
    return srv;
}


void destroyService(Service* srv) {
    /*
    destroys all the data in the service at the end of the program
    Service* srv: the service from which the data will be freed
    */
    if (srv) {
        if (srv->repo) {

            free(srv->repo->countries);
            free(srv->repo);
        }
        free(srv);
    }
}


int add_country_controller(Service* srv, char* name, char* continent, int population) {
    /*
    adds a new country by using already defined function
    return: the function from repo
    */
    if (population < 0) {
        return 3;
    }
    Operation op;
    op.type = ADD_COUNTRY;
    strcpy(op.country.name, name);
    strcpy(op.country.continent, continent);
    op.country.population = population;

    pushUndo(op);

    return add_country(srv->repo, name, continent, population);
}


int delete_country_controller(Service* srv, char* name) {
    /*
    deletes a new country by using already defined function
    return: the function from repo
    */

    //copied the part i need for searching the country
    int index = -1;
    for (int i = 0; i < get_vector_size(srv->repo); i++) {
        if (_stricmp(get_countries(srv->repo)[i].name, name) == 0) {
            index = i;
            Operation op;
            op.type = DELETE_COUNTRY;
            strcpy(op.country.name, get_countries(srv->repo)[i].name);
            strcpy(op.country.continent, get_countries(srv->repo)[i].continent);
            op.country.population = get_countries(srv->repo)[i].population;

            pushUndo(op);
            return delete_country(srv->repo, name);
        }
    }
    return 1;
}


int update_country_controller(Service* srv, char* name, char* new_continent, int new_population) {
    /*
    updates a new country by using already defined function
    return: the function from repo
    */
    int index = -1;
    for (int i = 0; i < get_vector_size(srv->repo); i++) {
        if (_stricmp(get_countries(srv->repo)[i].name, name) == 0) {
            index = i;

            Operation op;
            op.type = UPDATE_COUNTRY;
            strcpy(op.country.name, get_countries(srv->repo)[i].name);
            strcpy(op.country.continent, new_continent);
            op.country.population = new_population;
            if (new_continent != NULL && strlen(new_continent) > 0) {
                strcpy(op.prevName, get_countries(srv->repo)[i].continent);
            }
            op.prevPopulation = get_countries(srv->repo)[i].population;
            pushUndo(op);

            if (new_continent != NULL && strlen(new_continent) > 0) {
                if (!is_valid_continent(new_continent)) {
                    return 2;
                }
                strcpy(get_countries(srv->repo)[i].continent, new_continent);
            }

            if (new_population >= 0) {
                get_countries(srv->repo)[i].population = new_population;
            }

            return 0;
        }
    }
    return 1;
}

int migrate_population_controller(Service* srv, char* from, char* to, int people) {
    /*
    takes a part of the population from one country and moves it to the other one
    return: the function from repo
    */

    int from_index = -1, to_index = -1;
    for (int i = 0; i < get_vector_size(srv->repo); i++) {
        if (_stricmp(get_countries(srv->repo)[i].name, from) == 0) {
            from_index = i;
        }
        if (_stricmp(get_countries(srv->repo)[i].name, to) == 0) {
            to_index = i;
        }
    }
    if (from_index == -1) {
        return 1;
    }
    if (to_index == -1) {
        return 2;
    }
    if (get_countries(srv->repo)[from_index].population < people) {
        return 3;
    }
    Operation op;
    op.type = MIGRATE_POPULATION;
    strcpy(op.country.name, from);
    strcpy(op.prevName, to);
    op.country.population = people;
    op.prevPopulation = get_countries(srv->repo)[from_index].population;
    op.prevPopulationTo = get_countries(srv->repo)[to_index].population;
    pushUndo(op);
    return migrate_population(srv->repo, from, to, people);

}


Country* search_country_controller(Service* srv, char* query, int* result_count) {
    /*
    searches a  country by using already defined function
    return: the function from repo
    */
    return search_country(srv->repo, query, result_count);
}


void redo(Service* srv) {
    /*
    operation for redo-ing the last command
    Service* srv: the service on which the operation is done
    */
    if (redoTop == -1) {
        printf("No operations to redo.\n");
        return;
    }
    Operation op;
    memcpy(&op, &redoStack[redoTop--], sizeof(Operation));

    switch (op.type) {
    case ADD_COUNTRY:
        add_country(srv->repo, op.country.name, op.country.continent, op.country.population);
        break;
    case DELETE_COUNTRY:
        delete_country(srv->repo, op.country.name);
        break;
    case UPDATE_COUNTRY:
        update_country(srv->repo, op.country.name, op.country.continent, op.country.population);
        break;

    case MIGRATE_POPULATION:
        for (int i = 0; i < get_vector_size(srv->repo); i++) {
            if (_stricmp(get_countries(srv->repo)[i].name, op.country.name) == 0) {
                get_countries(srv->repo)[i].population -= op.country.population;
            }
            if (_stricmp(get_countries(srv->repo)[i].name, op.prevName) == 0) {
                get_countries(srv->repo)[i].population += op.country.population;
            }
        }
        break;
    }
    pushUndo(op);
}
void undo(Service* srv) {
    /*
    undo operation for the last command from add, delete, update or migrate
    Service* srv: the service on which the operation is done
    */
    if (undoTop == -1) {
        printf("No operations to undo.\n");
        return;
    }

    Operation op = undoStack[undoTop--];

    switch (op.type) {
    case ADD_COUNTRY:
        delete_country(srv->repo, op.country.name);
        break;
    case DELETE_COUNTRY:
        add_country(srv->repo, op.country.name, op.country.continent, op.country.population);
        break;
    case UPDATE_COUNTRY:
        update_country(srv->repo, op.country.name, op.prevName, op.prevPopulation);
        break;
    case MIGRATE_POPULATION:
        for (int i = 0; i < get_vector_size(srv->repo); i++) {
            if (_stricmp(get_countries(srv->repo)[i].name, op.country.name) == 0) {
                get_countries(srv->repo)[i].population = op.prevPopulation;
            }
            if (_stricmp(get_countries(srv->repo)[i].name, op.prevName) == 0) {
                get_countries(srv->repo)[i].population = op.prevPopulationTo;
            }
        }
        break;
    }
    pushRedo(op);
}



void pushUndo(Operation op) {
    /*
    pushing the operation on the undo stack for later usage
    Operation op: the operation of type undo
    */
    if (undoTop < 99) {
        memcpy(&undoStack[++undoTop], &op, sizeof(Operation));
        // redoTop = -1; 
    }
}

void pushRedo(Operation op) {
    /*
    pushing the operation on the redo stack for later usage
    Operation op: the operation of type redo
    */
    if (redoTop < 99) {
        memcpy(&redoStack[++redoTop], &op, sizeof(Operation));
    }
}



int compare_population(const void* a, const void* b) {
    /*
    comparing the population of 2 countries
    const void* a: first country
    const void* b: second country
    */

    Country* contryA = (Country*)a;
    Country* contryB = (Country*)b;
    return (contryA->population - contryB->population);
}

Country* search_by_continent(Service* srv, char* continent, int* result_count, int min_population) {
    /*
    searching all the countries after a given continent and displaying them sorted ascending after population
    Service* srv: the service in which the countries are saved
    char* continent: the continent given for search (for NULL all continents are considered)
    int* result_count: the number of countries found in that continent that satisfy the condition imposed
    int min_population: the minimum population imposed by the user
    */

    *result_count = 0;
    Country* res = (Country*)malloc(get_vector_size(srv->repo) * sizeof(Country));
    if (res == NULL) {
        return NULL;
    }
    for (int i = 0; i < get_vector_size(srv->repo); i++) {
        if ((strlen(continent) == 0 || _stricmp(get_countries(srv->repo)[i].continent, continent) == 0) && get_countries(srv->repo)[i].population > min_population) {
            res[*result_count] = get_countries(srv->repo)[i];
            (*result_count)++;
        }
    }
    if (*result_count == 0) {
        free(res);
        return NULL;
    }
    qsort(res, *result_count, sizeof(Country), compare_population);
    return res;
}

int delete_countries_by_continent_controller(Service* srv, char* continent) {
    int deleted_count = 0;
    for (int i = 0; i < get_vector_size(srv->repo); i++) {
        if (_stricmp(get_countries(srv->repo)[i].continent, continent) == 0) {
            Operation op;
            op.type = DELETE_COUNTRY;
            strcpy(op.country.name, get_countries(srv->repo)[i].name);
            strcpy(op.country.continent, get_countries(srv->repo)[i].continent);
            op.country.population = get_countries(srv->repo)[i].population;

            pushUndo(op);
            delete_country(srv->repo, get_countries(srv->repo)[i].name);
            i--;
            deleted_count++;
        }
    }

    return deleted_count;
}


