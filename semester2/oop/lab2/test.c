#include "country.h"
#include "country_vector.h"
#include "controller.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//country (domain)
void test_is_valid_continent() {
    assert(is_valid_continent("Europe") == 1);
    assert(is_valid_continent("America") == 1);
    assert(is_valid_continent("Africa") == 1);
    assert(is_valid_continent("Australia") == 1);
    assert(is_valid_continent("Asia") == 1);
    assert(is_valid_continent("Antarctica") == 0);
    assert(is_valid_continent("Mars") == 0);
    printf("test_is_valid_continent passed!\n");
}

void test_country_functions() {
    Country country;

    set_country_name(&country, "France");
    assert(strcmp(get_country_name(&country), "France") == 0);

    set_country_continent(&country, "Europe");
    assert(strcmp(get_country_continent(&country), "Europe") == 0);

    set_country_continent(&country, "Mars");
    assert(strcmp(get_country_continent(&country), "Europe") == 0);

    set_country_population(&country, 67);
    assert(get_country_population(&country) == 67);

    set_country_population(&country, -5000);
    assert(get_country_population(&country) == 67);

    printf("test_country_functions passed!\n");
}

//repo tests
void test_init_vector() {
    Repository repo;
    assert(init_vector(&repo) == 0);
    assert(get_vector_size(&repo) == 0);
    assert(get_vector_capacity(&repo) == INITIAL_CAPACITY);
    free_repository(&repo);
    printf("test_init_vector passed!\n");
}

void test_add_country() {
    Repository repo;
    init_vector(&repo);
    assert(add_country(&repo, "France", "Europe", 67) == 0);
    assert(get_vector_size(&repo) == 1);
    assert(strcmp(get_countries(&repo)[0].name, "France") == 0);

    assert(add_country(&repo, "France", "Europe", 67) == 1);
    assert(add_country(&repo, "Unknown", "Mars", 50) == 2);

    free_repository(&repo);
    printf("test_add_country passed!\n");
}

void test_delete_country() {
    Repository repo;
    init_vector(&repo);
    add_country(&repo, "France", "Europe", 67);
    assert(delete_country(&repo, "France") == 0);
    assert(get_vector_size(&repo) == 0);
    assert(delete_country(&repo, "Germany") == 1);

    free_repository(&repo);
    printf("test_delete_country passed!\n");
}

void test_update_country() {
    Repository repo;
    init_vector(&repo);
    add_country(&repo, "France", "Europe", 670);
    assert(update_country(&repo, "France", "Asia1", 50) == 2);
    assert(update_country(&repo, "France", "Europe", 700) == 0);
    assert(get_countries(&repo)[0].population == 700);
    assert(update_country(&repo, "Germany", "Europe", 80) == 1);

    free_repository(&repo);
    printf("test_update_country passed!\n");
}

void test_migrate_population() {
    Repository repo;
    init_vector(&repo);
    add_country(&repo, "France", "Europe", 67);
    add_country(&repo, "Germany", "Europe", 80);
    assert(migrate_population(&repo, "France", "Germany", 5) == 0);
    assert(get_countries(&repo)[0].population == 62);
    assert(get_countries(&repo)[1].population == 85);
    assert(migrate_population(&repo, "France", "Italy", 5) == 2);
    assert(migrate_population(&repo, "Spain", "Germany", 5) == 1);
    assert(migrate_population(&repo, "France", "Germany", 70) == 3);

    free_repository(&repo);
    printf("test_migrate_population passed!\n");
}

void test_search_country() {
    Repository repo;
    init_vector(&repo);
    add_country(&repo, "France", "Europe", 67);
    add_country(&repo, "Germany", "Europe", 80);
    add_country(&repo, "Finland", "Europe", 55);

    int result_count;
    Country* results = search_country(&repo, "Fr", &result_count);
    assert(result_count == 1);
    assert(strcmp(results[0].name, "France") == 0);
    free(results);

    results = search_country(&repo, "land", &result_count);
    assert(result_count == 1);
    assert(strcmp(results[0].name, "Finland") == 0);
    free(results);

    results = search_country(&repo, "XYZ", &result_count);
    assert(results == NULL);

    free_repository(&repo);
    printf("test_search_country passed!\n");
}


//service
void test_undo_redo() {
    Service* srv = create_service();
    add_country_controller(srv, "France", "Europe", 67);
    undo(srv);
    assert(get_vector_size(srv->repo) == 0);
    redo(srv);
    assert(get_vector_size(srv->repo) == 1);

    add_country_controller(srv, "Germany", "Europe", 80);
    migrate_population_controller(srv, "France", "Germany", 5);
    undo(srv);
    assert(get_countries(srv->repo)[0].population == 67);
    assert(get_countries(srv->repo)[1].population == 80);
    redo(srv);
    assert(get_countries(srv->repo)[0].population == 62);
    assert(get_countries(srv->repo)[1].population == 85);

    destroyService(srv);
    printf("test_undo_redo passed!\n");
}

void test_undo_redo_better() {
    Repository repo;
    init_vector(&repo);
    Service srv;
    srv.repo = &repo;

    add_country(&repo, "France", "Europe", 67);
    pushUndo((Operation) { .type = ADD_COUNTRY, .country = { "France", "Europe", 67 } });
    assert(get_vector_size(&repo) == 1);

    undo(&srv);
    assert(get_vector_size(&repo) == 0);

    redo(&srv);
    assert(get_vector_size(&repo) == 1);
    assert(strcmp(get_countries(&repo)[0].name, "France") == 0);

    pushUndo((Operation) { .type = DELETE_COUNTRY, .country = { "France", "Europe", 67 } });
    delete_country(&repo, "France");
    assert(get_vector_size(&repo) == 0);

    undo(&srv);
    assert(get_vector_size(&repo) == 1);

    redo(&srv);
    assert(get_vector_size(&repo) == 0);

    free_repository(&repo);
    printf("test_undo_redo 2 passed!\n");
}


void call_all_tests() {
    test_is_valid_continent();
    test_country_functions();
    test_add_country();
    test_delete_country();
    test_init_vector();
    test_is_valid_continent();
    test_migrate_population();
    test_search_country();
    test_update_country();
    test_undo_redo();
    test_undo_redo_better();
}





