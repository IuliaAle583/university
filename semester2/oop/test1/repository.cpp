#include "repository.h"

bool Repository::remove(string& name, string& address)
{
    for (int i = 0; i < schools.getSize(); i++) {
        if (schools[i].getName() == name && schools[i].getAddress() == address) {
            schools.remove(i);
            return true;
        }
    }
    return false;
}

DynamicVector<School> Repository::getAll()
{
	return this->schools;
}

void Repository::markSchools(Date d)
{
    DynamicVector<School> schools = getAll();
    bool visited = false;
    for (int i = 0; i < schools.getSize(); i++) {

    }
}

//void Repository::markSchoolsVisitedBeforeDate(Date d) {
  //  for (int i = 0; i < schools.getSize(); i++) {
    //    if (schools[i].getDate() < d) {
    //        schools[i].setValue(false); 
    //    }
    //}
//}
