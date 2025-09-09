#include "Workout.h"
using namespace std;

Workout::Workout(int startHour, int endHour, const string& type, int intensity, const string& description)
    : startHour(startHour), endHour(endHour), type(type), intensity(intensity), description(description) {}

int Workout::getStartHour() const {
    return startHour;
}

int Workout::getEndHour() const {
    return endHour;
}

string Workout::getType() const {
    return type;
}

int Workout::getIntensity() const {
    return intensity;
}

string Workout::getDescription() const {
    return description;
}

int Workout::getDuration() const {
    return endHour - startHour;
}