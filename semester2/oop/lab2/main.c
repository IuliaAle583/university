#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "country_vector.h"
#include "controller.h"
#include "test.h"

void initialize_vector(Service* srv) {
    add_country_controller(srv, "France", "Europe", 67);
    add_country_controller(srv, "Germany", "Europe", 83);
    add_country_controller(srv, "Brazil", "America", 213);
    add_country_controller(srv, "Canada", "America", 38);
    add_country_controller(srv, "Australia", "Australia", 26);
    add_country_controller(srv, "China", "Asia", 1400);
    add_country_controller(srv, "India", "Asia", 1393);
    add_country_controller(srv, "South Africa", "Africa", 59);
    add_country_controller(srv, "Japan", "Asia", 126);
    add_country_controller(srv, "United Kingdom", "Europe", 68);
}

int main() {
    Service* srv = create_service();
    initialize_vector(srv);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int choice;
    char name[50], continent[20], from[50], to[50];
    int population, people;
    int last_deleted_count = 0;

    while (1) {
        printf("\n1. Add Country\n2. Delete Country\n3. Update Country\n4. Migrate Population\n5. Search Country\n6. Search for a continent\n7. Undo\n8. Redo\n9. Tests\n10. Exit\n11. Delete all contries on a continent\n12. Undo all\n13. Redo all\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Enter name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            printf("Enter continent: ");
            fgets(continent, 20, stdin);
            continent[strcspn(continent, "\n")] = 0;
            printf("Enter population (millions): ");
            scanf("%d", &population);

            int result = add_country_controller(srv, name, continent, population);
            if (result == 1) {
                printf("Error: Country already exists!\n");
            }
            else if (result == 2) {
                printf("Error: Invalid continent!\n");
            }
            else if (result == 3) {
                printf("Error: Population must be positive!\n");
            }
            else {
                printf("Country added successfully!\n");
            }
            break;

        case 2:
            printf("Enter name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            result = delete_country_controller(srv, name);
            if (result == 1) {
                printf("Error: Country not found!\n");
            }
            else {
                printf("Country deleted successfully!\n");
            }
            break;

        case 3:
            printf("Enter name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            printf("Enter new continent (enter the same as before if you want to keep it): ");
            fgets(continent, 20, stdin);
            continent[strcspn(continent, "\n")] = 0;
            printf("Enter new population (enter the same as before if you want to keep it): ");
            scanf("%d", &population);
            if (population < 0) {
                printf("Error: Population must be positive!\n");
            }
            else {
                result = update_country_controller(srv, name, continent, population);
                if (result == 1) {
                    printf("Error: Country not found!\n");
                }
                else if (result == 2) {
                    printf("Error: Invalid continent!\n");
                }
                else {
                    printf("Country updated successfully!\n");
                }
            }
            break;

        case 4:
            printf("Enter country migrating from: ");
            fgets(from, 50, stdin);
            from[strcspn(from, "\n")] = 0;
            printf("Enter country migrating to: ");
            fgets(to, 50, stdin);
            to[strcspn(to, "\n")] = 0;
            printf("Enter number of people migrating (in mil): ");
            scanf("%d", &people);

            result = migrate_population_controller(srv, from, to, people);
            if (result == 1) {
                printf("Error: Country migrating from not found!\n");
            }
            else if (result == 2) {
                printf("Error: Country migrating to not found!\n");
            }
            else if (result == 3) {
                printf("Error: Not enough population in the country migrating from!\n");
            }
            else {
                printf("Migration successful!\n");
            }
            break;

        case 5:
            printf("Enter search query: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;

            int count;
            Country* found_countries = search_country_controller(srv, name, &count);
            if (found_countries == NULL) {
                printf("Error: No countries found with that name.\n");
            }
            else {
                printf("Search results:\n");
                for (int i = 0; i < count; i++) {
                    printf("%s - %s - %d million\n", found_countries[i].name, found_countries[i].continent, found_countries[i].population);
                }
                free(found_countries);
            }
            break;

        case 6:
            printf("Enter continent (or press Enter to list all countries): ");
            fgets(continent, 20, stdin);
            continent[strcspn(continent, "\n")] = 0;
            int min_pop;
            printf("Enter minimum population (in millions): ");
            scanf("%d", &min_pop);
            getchar();

            int nr;
            Country* found_ctrys = search_by_continent(srv, continent, &nr, min_pop);
            if (found_ctrys == NULL) {
                printf("No countries found for the specified continent.\n");
            }
            else {
                printf("Countries in continent '%s':\n", (strlen(continent) == 0) ? "All" : continent);
                for (int i = 0; i < nr; i++) {
                    printf("%s - %s - %d million\n", found_ctrys[i].name, found_ctrys[i].continent, found_ctrys[i].population);
                }
                free(found_ctrys);
            }
            break;

        case 7:
            undo(srv);
            break;

        case 8:
            redo(srv);
            break;

        case 9:
            call_all_tests();
            printf("All tests passed successfully.\n");
            break;

        case 10:

            destroyService(srv);
            _CrtDumpMemoryLeaks();
            return 0;

        case 11:
            printf("Enter continent to delete all countries from: ");
            fgets(continent, 20, stdin);
            continent[strcspn(continent, "\n")] = 0;
            int deleted = delete_countries_by_continent_controller(srv, continent);
            last_deleted_count = deleted;
            if (deleted == 0) {
                printf("No countries found on this continent.\n");
            }
            else {
                printf("%d countries deleted successfully.\n", deleted);
            }
            break;
        case 12:
            if (last_deleted_count > 0) {
                for (int i = 0; i < last_deleted_count; i++) {
                    undo(srv);
                }
                printf("Undo completed for %d deletions.\n", last_deleted_count);
            }
            else {
                printf("No recent deletions to undo.\n");
            }
            break;
        case 13:
            if (last_deleted_count > 0) {
                for (int i = 0; i < last_deleted_count; i++) {
                    redo(srv);
                }
                printf("Redo completed for %d deletions.\n", last_deleted_count);
            }
            else {
                printf("No recent deletions to redo.\n");
            }
            break;

        }
    }
}
