
#pragma once
#include <string>
using namespace std;

class Workout {
private:
    int startHour;
    int endHour;
    string type;
    int intensity;
    string description;

public:
    Workout(int startHour, int endHour, const string& type, int intensity, const string& description);

    int getStartHour() const;
    int getEndHour() const;
    string getType() const;
    int getIntensity() const;
    string getDescription() const;

    int getDuration() const; 
};