#include "Domain.h"

string Domain::toString()
{
    string result = name + " | ";
    for (auto key : keywords) {
        result += key + ",";
    }
    return result;
}
