#include <iostream>
#include <cassert>
#include "Service.h"

void testGetAllVegetablesBelongingToFamily() {
    Service service;

    auto result = service.getAllVegetablesBelongingToFamily("Potato");
    assert(result.size() == 2); 
    for (const auto& veg : result) {
        assert(veg.getFamily() == "Potato");
    }

    auto emptyResult = service.getAllVegetablesBelongingToFamily("HJBHB");
    assert(emptyResult.empty());

}
