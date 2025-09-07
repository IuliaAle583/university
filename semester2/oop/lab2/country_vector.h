#pragma once
#include "country.h"


#define INITIAL_CAPACITY 10

typedef struct {
    Country* countries;
    int size;
    int capacity;
} Repository;



void free_repository(Repository* vec);
Country* get_countries(const Repository* vec);
int get_vector_size(const Repository* vec);
int get_vector_capacity(const Repository* vec);
void set_countries(Repository* vec, Country* countries, int size);
void set_vector_size(Repository* vec, int size);
void set_vector_size(Repository* vec, int size);
void set_vector_capacity(Repository* vec, int capacity);
int init_vector(Repository* vec);
int resize_vector(Repository* vec);
int add_country(Repository* vec, char* name, char* continent, int population);
int delete_country(Repository* vec, char* name);
int update_country(Repository* vec, char* name, char* new_continent, int new_population);
int migrate_population(Repository* vec, char* from, char* to, int people);
//int search_country(CountryVector* vec, char* query);
Country* search_country(Repository* vec, char* query, int* result_count);

