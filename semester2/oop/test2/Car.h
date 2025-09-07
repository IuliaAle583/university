#pragma once
#include "Domain.h"
class Car
{
private:
	int numberOfDoors;
    Engine* engine;
public:
    Car(int nrDoors, Engine* engine) : numberOfDoors(nrDoors), engine(engine) {};
    ~Car();
    double computePrice() const;
    string toString() const;
    int getNrOfDoors() { return this->numberOfDoors; };
};

