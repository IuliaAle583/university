#include "service.h"

void Service::initialise()
{
    
    Date date1(10, 5, 2020);   
    Date date2(15, 8, 2023);   
    Date date3(23, 11, 2025);  
    Date date4(7, 2, 2024);    

    School school1("Liceul_Teoretic", "46.77, 23.60", date1, false);
    School school2("Colegiul_National", "46.77, 23.58", date2, false);
    School school3("Scoala_Generala", "46.77, 23.63", date3, false);
    School school4("Liceul_de_Arte", "46.53, 24. 57", date4, true);

    repo.append(school1);
    repo.append(school2);
    repo.append(school3);
    repo.append(school4);
}

Service::Service(Repository& repository) : repo(repository) {
    initialise();
}

Service::~Service() {
    
}


/*
remove a school
string&name= the name
string& address= the address*/
bool Service::removeService(string& name, string& address)
{
	return repo.remove(name, address);
}

DynamicVector<School> Service::showAllSchools() {
    
    DynamicVector<School> schools = repo.getAll();

    sort(schools.begin(), schools.end(), [](const School& a, const School& b) {
        return a.getName() < b.getName();
        });

    return schools;
}


/*
mark schools as visited
Date d: the date before the mark
*/
void Service::markSchoolsVisitedBeforeDate(Date d) {
    DynamicVector<School>& schools = repo.get();

    for (int i = 0; i < schools.getSize(); i++) {
        if (schools[i].getDate() < d) {
            schools[i].setValue(false);
        }
    }
}

DynamicVector<School> Service::showSchoolsToBeVisitedAfterDate(Date d) {
    DynamicVector<School> schoolsToVisit;

    DynamicVector<School> schools = repo.getAll();

    for (int i = 0; i < schools.getSize(); i++) {
        if (schools[i].getDate() > d && !schools[i].getValue()) {
            schoolsToVisit.append(schools[i]);
        }
    }

    return schoolsToVisit;
}
