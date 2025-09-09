#include "ui.h"
#include <iostream>
using namespace std;

void UI::initial()
{
    DynamicVector<string> sensors1;
    sensors1.append("Temperature");
    sensors1.append("Humidity");

    DynamicVector<string> sensors2;
    sensors2.append("Pressure");
    sensors2.append("Humidity");
    string location, name;
    location = "new york";
    name = "central park";
    service.add(location, name, sensors1);  
    location = "new york";
    name = "jfk airport";
    service.add(location, name, sensors2); 
    location = "london";
    name = "greenwich";
    service.add(location, name, sensors1);
}

UI::UI()
{
    this->service = Service();
    initial();
}

UI::UI(Service service)
{
    this->service = service;
    initial();
}

void UI::run()
{
    int choice;
    while (true) {
        cout << "1. add\n2. show all\n3. ...\n";
        cout << "enter option";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "loction\n";
            string location;
            cin >> location;
            cin.ignore();
            string name;
            cout << "name\n";
            cin >> name;
            //cin.ignore();
            DynamicVector<string> sensors;
            int numSensors;

            cout << "Enter the number of sensors:\n ";
            cin >> numSensors; 

            
            for (int i = 0; i < numSensors; ++i) {
                string sensor;
                cout << "Enter sensor #" << i + 1 << ": ";
                cin >> sensor;
                sensors.append(sensor);  
            }
            if (this->service.add(location, name, sensors)) {
                cout << "success\n";
            }
            else {
                cout << "fail\n";
            }
        }
        else if (choice == 2) {
            DynamicVector<Weather> result = this->service.getAllService();
            for (int i = 0; i < result.getSize(); i++) {
                cout << result[i].getLocation() << "|" << result[i].getName() << "|";
                DynamicVector<string>& sensors = result[i].getSensors();

                for (int j = 0; j < sensors.getSize(); j++) {
                    cout << sensors[j]; 
                    if (j < sensors.getSize() - 1) {
                        cout << ", ";  
                    }
                }
                cout << endl;
            }
        }
        else if (choice == 3) {
            cout << "enter sensor\n";
            string sensor;
            cin >> sensor;
            cin.ignore();
            DynamicVector<pair<string, int>> result = this->service.countStationsBySensorService(sensor);
            if (result.getSize() > 0) {
                cout << "Stations with the sensor '" << sensor << "':" << endl;
                for (int i = 0; i < result.getSize(); i++) {
                    cout << "Location: " << result[i].first << ", Count: " << result[i].second << endl;
                }
            }
            else {
                cout << "No stations found with the sensor '" << sensor << "'." << endl;
            }

        }
        else {
            break;
        }
    }
}
