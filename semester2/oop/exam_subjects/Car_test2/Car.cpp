#include "Car.h"
#include <string>

double Car::computePrice()
{
    double price = 8000 * this->engine->getPrice();
    if (this->bodyStyle == "Convertible")
        price += 1000;
    return price;
}

void Car::destroyEngine()
{
    delete this->engine;
}

string Car::toString()
{
    return "Body style: " + this->bodyStyle + "\n" + this->engine->toString() + "Price of car: " + to_string(this->computePrice()) + "\n";
}
