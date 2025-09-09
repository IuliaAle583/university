#include <cassert>
#include <iostream>
#include "domain.h"
#include "repository.h"
#include "service.h"

void testAddCar() {
    Repository repo;
    Service service(repo);
    Car car1("CarName1", "Model1", 2020, "Red");
    bool result1 = service.addCar(car1);
    assert(result1 == true);  

    Car car2("CarName1", "Model1", 2020, "Blue");
    bool result2 = service.addCar(car2);
    assert(result2 == false);  

    Car car3("CarName2", "Model2", 2020, "Green");
    bool result3 = service.addCar(car3);
    assert(result3 == true);  

    Car car4("CarName1", "Model1", 2021, "Yellow");
    bool result4 = service.addCar(car4);
    assert(result4 == true);  

    std::cout << "Testele pentru addCar au fost trecute cu succes!" << std::endl;
}

void testGetVintageCarsSorted() {
    Repository repo;
    Service service(repo);

    repo.addCar(Car("CarName1", "Model1", 1970, "Red"));
    repo.addCar(Car("CarName2", "Model2", 1960, "Blue"));
    int size1;
    Car* vintageCars1 = service.getVintageCarsSorted(size1);
    //assert(size1 == 2);  
    assert(vintageCars1[0].get_color() == "Blue");  
    assert(vintageCars1[1].get_color() == "Red");

    repo.addCar(Car("CarName3", "Model3", 2020, "Yellow"));
    int size2;
    Car* vintageCars2 = service.getVintageCarsSorted(size2);
    //assert(size2 == 2);  
    assert(vintageCars2[0].get_color() == "Blue");
    assert(vintageCars2[1].get_color() == "Red");

    repo.addCar(Car("CarName4", "Model4", 2021, "Green"));
    int size3;
    Car* vintageCars3 = service.getVintageCarsSorted(size3);
    //assert(size3 == 0);  

    repo.addCar(Car("CarName5", "Model5", 1930, "Green"));
    int size4;
    Car* vintageCars4 = service.getVintageCarsSorted(size4);
    //assert(size4 == 3); 
    assert(vintageCars4[1].get_color() == "Green");
    assert(vintageCars4[0].get_color() == "Blue");
    assert(vintageCars4[2].get_color() == "Red");

    std::cout << "Testele pentru getVintageCarsSorted au fost trecute cu succes!" << std::endl;
}

void callAllTests() {
    testAddCar();
    testGetVintageCarsSorted();
   // return 0;
}
