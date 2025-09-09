#include "Domain.h"

bool NeonatalUnit::isEfficient()
{
    if (averageGrade >= 8.5 && numberOfNewborns >= numberOfMothers)
        return true;
    return false;
}

string NeonatalUnit::toString()
{
    return "Neonatal Unit\n "+HospitalDepartment::toString()+"Average grade "+to_string(averageGrade)+"\n"+"Number of mothers "+ to_string(numberOfMothers)+"\n"+"Number of newborns "+to_string(numberOfNewborns)+"\n";
}

bool Surgery::isEfficient()
{
    double percentage;
    percentage = (double)numberOfPatients / (double)numberOfDoctors;
    return percentage >= 2;
}

string Surgery::toString()
{
    return "Surgery Unit\n"+HospitalDepartment::toString()+"Number of patients "+ to_string(numberOfPatients)+"\n";
}

string HospitalDepartment::toString()
{
    return "Hospital name " + hospitalName + "\n" + "Number of doctors  " + to_string(numberOfDoctors) + "\n";
}
