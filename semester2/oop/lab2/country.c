#include "country.h"
#include <string.h>
#include <ctype.h>

const char* valid_continents[] = { "Europe", "America", "Africa", "Australia", "Asia" };

int is_valid_continent(char* continent) {
    /*
    validates a continent given by the user
    char* continent: the continent to validate
    */
    for (int i = 0; i < 5; i++) {
        if (_stricmp(continent, valid_continents[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

const char* get_country_name(const Country* country) {
    return country->name;
}

const char* get_country_continent(const Country* country) {
    return country->continent;
}

int get_country_population(const Country* country) {
    return country->population;
}

void set_country_name(Country* country, const char* name) {
    strncpy(country->name, name, sizeof(country->name) - 1);
    country->name[sizeof(country->name) - 1] = '\0';
}

void set_country_continent(Country* country, const char* continent) {
    if (is_valid_continent(continent)) {
        strncpy(country->continent, continent, sizeof(country->continent) - 1);
        country->continent[sizeof(country->continent) - 1] = '\0';
    }
}

void set_country_population(Country* country, int population) {
    if (population >= 0) {
        country->population = population;
    }
}
