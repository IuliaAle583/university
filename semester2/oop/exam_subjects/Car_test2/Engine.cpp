#include "Engine.h"
#include <string>

string Engine::toString()
{
    return "Base price: "+ to_string(basePrice)+"\n";
}

double ElectricEngine::getPrice()
{
    return Engine::getPrice()+ double(this->autonomy)*0.01;
}

string ElectricEngine::toString()
{
    return "Electric engine\nautonomy "+to_string(this->autonomy)+"\nprice "+to_string(this->getPrice())+"\n";
}

double TurboEngine::getPrice()
{
    return Engine::getPrice()+100;
}

string TurboEngine::toString()
{
    return "Turbo\nPrice " + to_string(this->getPrice()) + "\n";
}
