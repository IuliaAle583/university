#include "Dwelling.h"

double Dwelling::normalBankRate()
{
    return this->price/1000;
}

double Dwelling::largeBankRate()
{
    return this->price/100;
}
