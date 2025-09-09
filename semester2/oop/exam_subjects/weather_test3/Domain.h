#include <QtCharts/QChart>
#include <QtCharts/QChartView>


#pragma once
#include <vector>
#include <string>
using namespace std;

class weather {

private:
    int startHour;
    int endHour;
    int precipitation;
    string description;

public:

    static vector<string> tokenize(string str, char delimiter);
    friend istream& operator>>(istream&, weather&);
    weather();
    weather(int startHour, int endHour, int precipitation, string description);
    ~weather();
    int getStartHour();
    int getEndHour();
    int getPrecipitation();
    string getDescription();

};