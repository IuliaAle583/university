#pragma once
#include "DynamicVector.h"
#include "domain.h"
class Repository {
private:
	DynamicVector<School> schools;
public:
	Repository() = default;

	bool remove(string& name, string& address);
	DynamicVector<School> getAll();

	void append(const School& school) {
		schools.append(school);  
	}

	void markSchools(Date d);

	DynamicVector<School>& get() {
		return schools;
	}

	//void markSchoolsVisitedBeforeDate(Date d);

};
