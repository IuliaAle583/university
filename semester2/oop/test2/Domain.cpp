#include "Domain.h"
#include <iostream>
#include <string>
using namespace std;

string Engine::toString() const {
    return "The price is: " + to_string(basePrice);
}

double ElectricEngine::getPrice() const {
    return basePrice + autonomy * 0.01;
}

string ElectricEngine::toString() const {
    return "Electric Engine : Base: " + to_string(basePrice) +
        ", Autonomy: " + to_string(autonomy);
}

double TurboEngine::getPrice() const {
    return basePrice + 100;
}

string TurboEngine::toString() const {
    return "Turbo Engine : Base: " + to_string(basePrice);
}
