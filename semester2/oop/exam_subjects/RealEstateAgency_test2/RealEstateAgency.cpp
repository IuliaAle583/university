#include "RealEstateAgency.h"
#include <fstream>

void RealEstateAgency::init()
{
    this->dwellings.push_back(Dwelling("House", 60000, true));
    this->clients.push_back(new NormalClient("Ion", 700));
    this->clients.push_back(new NormalClient("Ana", 600));
    this->clients.push_back(new WealthyClient("BCR", 33343, 293021));
    this->clients.push_back(new WealthyClient("BRD", 10, 20));
}

Dwelling RealEstateAgency::addDwelling(string type, double price, bool isProfitable)
{
    Dwelling dwelling = Dwelling(type, price, isProfitable);
    dwellings.push_back(dwelling);
    return dwelling;
}

void RealEstateAgency::removeClient(string name)
{
    for (int i = 0; i < this->clients.size(); i++) {
        if (clients[i]->getName() == name) {
            clients.erase(clients.begin() + i);
            break;
        }
    }
}

vector<Client*> RealEstateAgency::getInterestedClients(Dwelling d)
{
    vector<Client*> interested;
    for (auto c : clients) {
        if (c->isInterested(d))
            interested.push_back(c);
        
    }
    return interested;
}

void RealEstateAgency::writeToFile(string filename)
{
    ofstream fout(filename);
    for (auto c : clients) {
        fout << c->toString() << "\n";
    }
}
