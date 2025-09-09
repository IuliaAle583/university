#pragma once
#include "service.h"
class UI {
private:
	Service service;
	void initial();
public:
	UI();
	UI(Service service);
	void run();
};
