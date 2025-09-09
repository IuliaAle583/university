#pragma once
#include "observer.h"
#include <vector>
#include <memory>	//pt unique ptr
using namespace std;

class Subject {
private:
	vector<unique_ptr<Observer>> observers;
public:
	Subject() = default;
	~Subject() = default;
	void registerObserver(Observer* obs) {
		observers.emplace_back(obs);
	}
	void notify() {
		for (auto& obs : observers) {
			obs->update();
		}
	}
};
