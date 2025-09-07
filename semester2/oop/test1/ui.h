#pragma once
#include "service.h"
class UI {
private:
	Service& service;
	void showMenu();  
	void handleShowAllSchools();
public:
	//UI();
	UI(Service& service);
	void run();
	void removeSchool();
	void showSchoolsToBeVisitedAfter();
	void markSchoolsVisitedBefore();

};
