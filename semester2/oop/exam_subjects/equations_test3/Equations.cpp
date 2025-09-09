#include "Equations.h"

string Equations::solve() const
{
    double d = getDiscriminant();
    if (d < 0) {
        return "x1= " + to_string(-b / (2 * a)) + "+" + to_string(sqrt(-d) / (2 * a)) + "i, x2=" +
            to_string(-b / (2 * a)) + "-" + to_string(sqrt(-d) / (2 * a)) + "i";
    }
    else if (d == 0) {
        return "x= " + to_string(-b / (2 * a));
    }
    else {
        return "x1= " + to_string((-b + sqrt(d)) / (2 * a))+ 
            ", x2= "+to_string((-b-sqrt(d))/(2*a));
    }
}
