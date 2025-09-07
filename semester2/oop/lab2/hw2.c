/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country_vector.h"
#include "controller.h"1

int main() {
    CountryVector vec;
    initVector(&vec);
    int choice;
    char name[50], continent[20], from[50], to[50];
    int population, people;

    while (1) {
        printf("\n1. Add Country\n2. Delete Country\n3. Update Country\n4. Migrate Population\n5. Search Country\n6. Display Countries\n7. Exit\n");
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
            addCountryController(&vec, name, continent, population);
            break;
        case 2:
            printf("Enter name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            deleteCountryController(&vec, name);
            break;
        case 3:
            printf("Enter name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            printf("Enter new continent (or press Enter to keep current): ");
            fgets(continent, 20, stdin);
            continent[strcspn(continent, "\n")] = 0;
            printf("Enter new population (-1 to keep current): ");
            scanf("%d", &population);
            updateCountryController(&vec, name, strlen(continent) > 0 ? continent : NULL, population);
            break;
        case 4:
            printf("Enter country migrating from: ");
            fgets(from, 50, stdin);
            from[strcspn(from, "\n")] = 0;
            printf("Enter country migrating to: ");
            fgets(to, 50, stdin);
            to[strcspn(to, "\n")] = 0;
            printf("Enter number of people migrating: ");
            scanf("%d", &people);
            migratePopulationController(&vec, from, to, people);
            break;
        case 5:
            printf("Enter search query: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            searchCountryController(&vec, name);
            break;
        case 6:
            displayCountriesController(&vec);
            break;
        case 7:
            free(vec.countries);
            return 0;
        }
    }
}
*/