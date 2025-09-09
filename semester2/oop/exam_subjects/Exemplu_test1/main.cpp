
#include <iostream>
#include "ui.h"
#include "test.h"

void initializeData(Service& service) {
    service.addCar(Car("Fiat", "Bravo", 2007, "red"));
    service.addCar(Car("Fiat", "Idea", 2003, "black"));
    service.addCar(Car("Audi", "A5", 2008, "blue"));
    service.addCar(Car("BMW", "Coupe", 2013, "pink"));
    service.addCar(Car("Ford", "Fiesta", 1976, "yellow"));
    service.addCar(Car("Mercedes", "C-Class", 1980, "white"));
    service.addCar(Car("Toyota", "Corolla", 1995, "green"));
    service.addCar(Car("Honda", "Civic", 2000, "silver"));
    service.addCar(Car("Volkswagen", "Golf", 1985, "gray"));
    service.addCar(Car("Peugeot", "206", 1998, "purple"));
}

int main()
{
    //std::cout << "Hello World!\n";
    Repository repo(10);
    Service service(repo);
    UI ui(service);
    initializeData(service);

    callAllTests();
    std::cout << "tests passed\n";

    ui.run();
    return 0;
}

