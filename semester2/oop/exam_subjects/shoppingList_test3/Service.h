#pragma once

#include "repository.h"
#include <algorithm>

class Service {
private:
    Repository repository;
public:
    static inline bool functionOfComparison(Item& item1, Item& item2) { return item1.getQuantity() < item2.getQuantity(); };
    std::vector<Item> getAllItems();
    std::vector<Item> getItemsByCategory(std::string category);
    std::vector<Item> getItemsThatContainString(std::string search);
};


