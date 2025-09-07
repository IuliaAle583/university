#pragma once
#include "country_vector.h"
typedef struct {
    Repository* repo;
} Service;

typedef enum {
    ADD_COUNTRY,
    DELETE_COUNTRY,
    UPDATE_COUNTRY,
    MIGRATE_POPULATION
} OperationType;

typedef struct {
    OperationType type;
    Country country;
    float prevPopulation;
    char prevName[50];
    float prevPopulationTo;
} Operation;

extern Operation undoStack[100];
extern int undoTop;
extern Operation redoStack[100];
extern int redoTop;

int add_country_controller(Service* srv, char* name, char* continent, int population);
int delete_country_controller(Service* srv, char* name);
int update_country_controller(Service* srv, char* name, char* new_continent, int new_population);
int migrate_population_controller(Service* srv, char* from, char* to, int people);
//int search_country_controller(CountryVector* vec, char* query);
//void displayCountriesController(CountryVector* vec);
Country* search_country_controller(Service* srv, char* query, int* result_count);
Country* search_by_continent(Service* srv, char* continent, int* result_count, int min_population);
int delete_countries_by_continent_controller(Service* srv, char* continent);
void* create_service();
void destroyService(Service* srv);

void undo(Service* srv);
void redo(Service* srv);
void pushUndo(Operation op);
void pushRedo(Operation op);