#include "domain.h"



string MedicalAnalysis::toString() const
{
    return "date: "+date+"\n";
}

bool BMI::isResultOK() const
{
    if (this->value >= 18.5 && this->value < 25)
        return true;
    return false;
}

string BMI::toString() const
{
    return "TYPE: BMI\n"+ MedicalAnalysis::toString()+"value: " + to_string(value) +"\n";
}

bool BP::isResultOK()  const
{
    if (this->systolic >= 90 && this->systolic <= 119 && this->diastolic>= 60 && this->diastolic <= 79)
        return true;
    return false;
}

string BP::toString() const
{
    return "TYPE: BP\n" + MedicalAnalysis::toString() + "systolic value: " + to_string(systolic) + "\n" + "diastolic value: " + to_string(diastolic) + "\n";
}
