#include "Appliance.h"

string Appliance::toString()
{
    return "ID: "+id+"\n";
}

double Refrigirator::consumedElectricity()
{
    double res=30;
    if (electricityUsageClass == "A") {
        res = res * 3;
    }
    else if (electricityUsageClass == "A++") {
        res = res * 2;
    }
    else if (electricityUsageClass == "A+") {
        res = res * 2.5;
    }
    if (hasFreezer) {
        res += 20;
    }
    return res;
}

string Refrigirator::toString()
{
    return "Refrigirator\n"+Appliance::toString()+"Electricity usage class: "+electricityUsageClass+"\nHas freezer"+to_string(hasFreezer)+"\n";
}

double DishWasher::consumedElectricity()
{
    double res=consumedElectricityForOneHour*20;
    return res;
}

string DishWasher::toString()
{
    return "DIshwasher\n"+Appliance::toString()+"Consumed electricity for one hour: "+to_string(consumedElectricityForOneHour)+"\n";
}
