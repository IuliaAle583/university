#include "tests.h"
#include "Service.h"
#include <cassert>
void testGetSorted() {
	Service service;
    
    double value = 100;
    auto sorted = service.getSorted(value);

    for (auto a : sorted) {
        assert(a->consumedElectricity() < value);
    }

    for (size_t i = 1; i < sorted.size(); ++i) {
        assert(sorted[i - 1]->getId() <= sorted[i]->getId());
    }

    std::cout << "test_getSorted passed!\n";
}
void callAllTests()
{
    testGetSorted();
}
