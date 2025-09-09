#pragma once
#include <iostream>
#include <string>
class Item
{
private:
    std::string category, name;
    int quantity;
public:
    Item(std::string category, std::string name, int quantity) : category{ category }, name{ name }, quantity{ quantity } {};
    std::string getCategory() const { return this->category; };
    std::string getName() const { return this->name; };
    int getQuantity() const { return this->quantity; };
    inline bool operator < (const Item& item) const {
        if (this->category == item.getCategory())
            return this->name < item.name;
        return this->category < item.category;
    };
    std::string toString() const
    {
        return this->category + " " + this->name + " " + std::to_string(this->quantity);
    }
};

