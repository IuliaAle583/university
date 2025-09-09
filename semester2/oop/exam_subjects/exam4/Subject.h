#pragma once
#include <vector>
#include "Observer.h"
using namespace std;

class Subject
{
private:
	vector<Observer*> observers;
public:
	Subject() = default;
	~Subject() = default;
	void registerObserver(Observer* obs) {
		this->observers.emplace_back(obs);
	}
	void notify() {
		for (auto& obs : observers) {
			obs->update();
		}
	}
};

