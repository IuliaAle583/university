#pragma once
#include "item.h"
#include <vector>
#include <sstream>
#include <fstream>

class Repository
{
private:
    std::vector<Item> items;
public:
    Repository() { this->loadFilesIntoRepo(); };
    void loadFilesIntoRepo();
    std::vector<Item> getItems();
};
