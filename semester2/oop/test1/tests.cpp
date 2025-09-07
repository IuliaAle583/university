#include "tests.h"
#include "service.h"
#include <cassert>

void testAdd() {
    Repository repo;

    Service service(repo);

    Date date1(10, 5, 2020);
    Date date2(15, 8, 2023);
    Date date3(23, 11, 2025);
    Date date4(7, 2, 2024);

    School school1("Liceul_Teoretic", "46.77, 23.60", date1, true);
    School school2("Colegiul_National", "46.77, 23.58", date2, true);
    School school3("Scoala_Generala", "46.77, 23.63", date3, false);
    School school4("Liceul_de_Arte", "46.53, 24.57", date4, true);

    repo.append(school1);
    repo.append(school2);
    repo.append(school3);
    repo.append(school4);

    //assert(repo.getAll().getSize() == 4);

    string name = school1.getName();
    string address = school1.getAddress();

    bool removed = service.removeService(name, address);

    assert(removed == true);  

}
void Mark() {
    Repository repo;
    Service service(repo);

    Date date1(10, 5, 2020);
    Date date2(15, 8, 2023);
    Date date3(23, 11, 2025);
    Date date4(7, 2, 2024);

    School school1("Liceul_Teoretic", "46.77, 23.60", date1, true);
    School school2("Colegiul_National", "46.77, 23.58", date2, true);
    School school3("Scoala_Generala", "46.77, 23.63", date3, false);
    School school4("Liceul_de_Arte", "46.53, 24.57", date4, true);

    repo.append(school1);
    repo.append(school2);
    repo.append(school3);
    repo.append(school4);

    assert(school1.getValue() == true);  
    assert(school2.getValue() == true);  
    assert(school3.getValue() == false); 
    assert(school4.getValue() == true); 

    Date testDate(1, 1, 2023);  

    service.markSchoolsVisitedBeforeDate(testDate);

    assert(school1.getValue() == false); 
    assert(school2.getValue() == false); 
    assert(school3.getValue() == false); 
    assert(school4.getValue() == true);  

    //std::cout << "Test passed!" << std::endl;
}

void callAllTests()
{
    testAdd();
}
