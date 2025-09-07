#include "Domain.h"
string Domain::toString()
{
    string result = name + " | ";
    for (auto key : keywords) {
        result += key + ",";
    }

    if (!keywords.empty()) {
        result.pop_back(); 
    }

    return result;
}
