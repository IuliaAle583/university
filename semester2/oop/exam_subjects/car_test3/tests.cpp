#include <cassert>
#include "Service.h"
#include "Repository.h"

void test_countCarsByManufacturer() {
    Repository repo;
    Service service;

    assert(service.countCarsByManufacturer("Dacia") == 1);
    assert(service.countCarsByManufacturer("Ford") == 1);
    assert(service.countCarsByManufacturer("Skoda") == 2);
    assert(service.countCarsByManufacturer("HJV") == 0);
    assert(service.countCarsByManufacturer("") == 0); 
}
