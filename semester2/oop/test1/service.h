#pragma once
#include "repository.h"

class Service {
private:
	Repository& repo;
	void initialise();
public:
	Service(Repository& repository);
	~Service();
	bool removeService(string& name, string& address);
	DynamicVector<School> showAllSchools();
	void markSchoolsVisitedBeforeDate(Date d);
	DynamicVector<School> showSchoolsToBeVisitedAfterDate(Date d);
	//void markSchoolsVisitedBeforeDate(Date d);
};
