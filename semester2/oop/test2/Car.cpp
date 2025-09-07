#include "Car.h"



Car::~Car() {
    delete engine;
}

double Car::computePrice() const {
    double doorPrice = (this->numberOfDoors == 2) ? 7000 : 8500;
    return doorPrice + engine->getPrice();
}

string Car::toString() const {
    return "Car: number of doors " + to_string(this->numberOfDoors) + ", Engine: " + engine->toString() +
        ", Total Price: " + to_string(computePrice());
}


