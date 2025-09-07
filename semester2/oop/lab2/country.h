#pragma once

typedef struct {
    char name[50];
    char continent[20];
    int population;
} Country;

int is_valid_continent(char* continent);
const char* get_country_name(const Country* country);
const char* get_country_continent(const Country* country);
int get_country_population(const Country* country);
void set_country_name(Country* country, const char* name);
void set_country_continent(Country* country, const char* continent);
void set_country_population(Country* country, int population);

