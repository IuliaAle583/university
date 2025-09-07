#include "domain.h"
#include "repository.h"
#include "service.h"
#include "tests.h"
#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

//domain tests
void testDomain() {
	TrenchCoat coat(1, 34, "blue", 4, 5, "jahsd");
	assert(coat.getId() == 1);
	assert(coat.getColour() == "blue");
	assert(coat.getPhotoLink() == "jahsd");
	assert(coat.getPrice() == 4);
	assert(coat.getSize() == 34);
	assert(coat.getQuantity() == 5);
	coat.setID(2);
	assert(coat.getId() == 2);
	coat.setColour("red");
	assert(coat.getColour() == "red");
	coat.setSize(36);
	assert(coat.getSize() == 36);
	coat.setPhotoLink("haha");
	assert(coat.getPhotoLink() == "haha");
	coat.setPrice(56);
	assert(coat.getPrice() == 56);
	coat.setQuantity(3);
	assert(coat.getQuantity() == 3);

	TrenchCoat other(1, 34, "blue", 4, 5, "jahsd");
	assert(!(coat == other));

	cout << "Domain tests passed!" << endl;

}

//dynamic array
void testDynamicArray() {
	DynamicVector <TrenchCoat> coats{ 1 };
    TrenchCoat trenchCoat1(1, 2, "red", 3, 4, "link");
    TrenchCoat trenchCoat2(2, 3, "blue", 4, 5, "link2");
    TrenchCoat trenchCoat3(3, 4, "green", 5, 6, "link3");
    TrenchCoat trenchCoat4(4, 5, "yellow", 6, 7, "link4");
    TrenchCoat trenchCoat5(5, 6, "black", 7, 8, "link5");
    TrenchCoat trenchCoat6(6, 7, "white", 8, 9, "link6");
    TrenchCoat trenchCoat7(7, 8, "purple", 9, 10, "link7");
    TrenchCoat trenchCoat8(8, 9, "orange", 10, 11, "link8");
    TrenchCoat trenchCoat9(9, 10, "brown", 11, 12, "link9");
    TrenchCoat trenchCoat10(10, 11, "grey", 12, 13, "link10");
    TrenchCoat trenchCoat11(11, 12, "pink", 13, 14, "link11");
    TrenchCoat trenchCoat12(12, 13, "cyan", 14, 15, "link12");
    TrenchCoat trenchCoat13(13, 14, "magenta", 15, 16, "link13");
    TrenchCoat trenchCoat14(14, 15, "lime", 16, 17, "link14");
    TrenchCoat trenchCoat15(15, 16, "maroon", 17, 18, "link15");
    TrenchCoat trenchCoat16(16, 17, "olive", 18, 19, "link16");
    TrenchCoat trenchCoat17(17, 18, "navy", 19, 20, "link17");

    coats.append(trenchCoat1);
    coats.append(trenchCoat2);
    coats.append(trenchCoat3);
    coats.append(trenchCoat4);
    coats.append(trenchCoat5);
    coats.append(trenchCoat6);
    coats.append(trenchCoat7);
    coats.append(trenchCoat8);
    coats.append(trenchCoat9);
    coats.append(trenchCoat10);
    coats.append(trenchCoat11);
    coats.append(trenchCoat12);
    coats.append(trenchCoat13);
    coats.append(trenchCoat14);
    coats.append(trenchCoat15);
    coats.append(trenchCoat16);
    coats.append(trenchCoat17);

    assert(coats.getSize() == 17);
    assert(coats.getCapacity() == 32);
    coats.remove(0);
    assert(coats.getSize() == 16);
    assert(coats.getCapacity() == 32);
    coats.remove(15);
    assert(coats.getSize() == 15);
    assert(coats.getCapacity() == 32);
    coats.update(0, trenchCoat1);
    assert(coats[0] == trenchCoat1);
    coats.update(-1, trenchCoat10);
    coats.remove(-1);
    assert(coats.getSize() == 15);
    cout << "Dynamic array tests passed!" << endl;
}

void testDynamicVectorAccess() {
    DynamicVector<int> vec;
    vec.append(10);  
    vec.append(20);

    assert(vec[0] == 10);
    assert(vec[1] == 20);
}


void testDynamicVectorAssignmentOperator() {
    DynamicVector<int> vec1;
    vec1.append(10);
    vec1.append(20);
    vec1.append(30);

    DynamicVector<int> vec2;
    vec2.append(99);  

    vec2 = vec1;  

    assert(vec2.getSize() == 3);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);
    assert(vec2[2] == 30);
}


#include <cassert>

void testDynamicVectorBeginEnd() {
    DynamicVector<int> vec;
    vec.append(5);
    vec.append(10);
    vec.append(15);

    int expected[] = { 5, 10, 15 };
    int i = 0;

    for (int* it = vec.begin(); it != vec.end(); ++it) {
        assert(*it == expected[i]);
        i++;
    }

    assert(i == 3); 
}



//repository tests
void testAdd() {
    Repository repository("testFile.txt");
    TrenchCoat trenchToAdd(1, 2, "red", 3, 4, "link");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    assert(repository.getSize() == 1);
    assert(repository.getAll()[0] == trenchToAdd);

    repository.addCoat(1, 5, "blue", 2, 4, "link");
    TrenchCoat trenchToUpdate(1, 5, "blue", 2, 4, "link");
    assert(repository.getSize() == 2);
    assert(repository.getAll()[1] == trenchToUpdate);

    std::cout << "AddTrenchCoat test passed!" << std::endl;
}

void testRemove() {
    Repository repository("testFile.txt");
    TrenchCoat trenchToAdd(1, 2, "red", 3, 4, "link");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    repository.removeCoat(-1);
    assert(repository.getSize() == 1);
    repository.removeCoat(1);
    assert(repository.getSize() == 0);
    std::cout << "RemoveTrenchCoat test passed!" << std::endl;
}

void testUpdate()
{
    Repository repository("testFile.txt");

    repository.addCoat(1, 2, "red", 3, 4, "link");
    repository.updateCoat(1, 1, 3, "blue", 4, 5, "link2");
    TrenchCoat trenchToUpdate(1, 3, "blue", 4, 5, "link2");
    assert(repository.getSize() == 1);
    assert(repository.getAll()[0] == trenchToUpdate);
    std::cout << "UpdateTrenchCoat test passed!" << std::endl;
}

void testGetCoat()
{
    Repository repository("testFile.txt");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    TrenchCoat trenchToAdd(1, 2, "red", 3, 4, "link");
    assert(repository.getCoat(1) == trenchToAdd);
    repository.removeCoat(1);

    assert(repository.getCoat(100) == TrenchCoat(-1, -1, "", -1, -1, ""));
    std::cout << "GetTrenchCoat test passed!" << std::endl;
}

void testGetAll()
{
    Repository repository("testFile.txt");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    TrenchCoat trenchToAdd(1, 2, "red", 3, 4, "link");
    assert(repository.getAll()[0] == trenchToAdd);
    repository.removeCoat(1);
    std::cout << "GetAllTrench coats test passed!" << std::endl;
}

void testGetSize()
{
    Repository repository("testFile.txt");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    assert(repository.getSize() == 1);
    repository.removeCoat(1);
    std::cout << "GetSize test passed!" << std::endl;
}

void testSetFileName()
{
    Repository repository("testFile.txt");
    repository.setFileName("testFile2.txt");
    assert(repository.getFileName() == "testFile2.txt");
    std::cout << "SetFile name test passed!" << std::endl;
}

void testWriteToFile()
{
    Repository repository("testFile.txt");
    TrenchCoat trenchToAdd(1, 2, "red", 3, 4, "link");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    repository.writeToFile();
    repository.removeCoat(1);
    assert(repository.getSize() == 0);
    repository.readFromFIle();
    assert(repository.getSize() == 1);
    assert(repository.getAll()[0] == trenchToAdd);
    repository.removeCoat(1);
    repository.writeToFile();
    std::cout << "WriteToFile test passed!" << std::endl;
}

void testCheckID()
{
    Repository repository("testFile.txt");
    repository.addCoat(1, 2, "red", 3, 4, "link");
    assert(repository.validID(1) == true);
    assert(repository.validID(2) == false);
    repository.removeCoat(1);
    std::cout << "ValidID test passed!" << std::endl;
}

//service tests
void testService()
{
    Repository repository;
    Service service(repository);
    service.setFileName("trenchsTest.txt");
    service.addCoat(1, 2, "red", 3, 4, "photo");
    assert(service.getSize() == 1);
    assert(service.checkIfExists(1) == 1);
    
    service.removeCoat(1);
    assert(service.getSize() == 0);

    service.addCoat(1, 2, "red", 3, 4, "photo");
    assert(service.getCoat(1).getColour() == "red");
    service.updateCoat(1, 3, 2, "blue", 3, 4, "photo");
    assert(service.getCoat(3).getColour() == "blue");

    service.updateCoat(3, 3, 2, "blue", 3, 4, "photo");
    assert(service.getSize() == 1);
    assert(service.updateCoat(5, 3, 2, "blue", 3, 4, "photo") == false);

    assert(service.getSize() == 1);
    assert(service.getFileName() == "trenchsTest.txt");

    service.saveProgress();
    service.setFileName("trenchsTest.txt");
    service.loadFile();

    service.addCoat(2, 3, "red", 3, 4, "photo");
    service.addCoat(3, 4, "red", 3, 4, "photo");
    service.addCoat(4, 4, "red", 3, 4, "photo");
    service.addCoat(5, 6, "red", 3, 4, "photo");
    service.addCoat(6, 6, "red", 3, 4, "photo");
    service.addCoat(7, 6, "red", 3, 4, "photo");
    assert(service.addCoat(7, 6, "red", 3, 4, "photo") == false);

    DynamicVector<TrenchCoat> filtered = service.filterBySize(6);
    assert(filtered.getSize() == 3);

    DynamicVector<TrenchCoat> all = service.getAll();
    assert(all.getSize() == 7);
}

void testCheckIfItExists()
{
    Repository repository;
    Service service(repository);
    service.setFileName("trenchsTest.txt");

    service.addCoat(1, 2, "red", 3, 4, "photo");
    assert(service.checkIfExists(1) == 1);
    assert(service.checkIfExists(2) == 0);

    std::cout << "Controller tests passed!" << std::endl;
}

void testServiceConstructor() {
    Service s;
    assert(s.getSize() == 0);
}

void callAllTests() {
	testDomain();
    testDynamicArray();
    testAdd();
    testRemove();
    testUpdate();
    testGetCoat();
    testGetAll();
    testGetSize();
    testSetFileName();
    testWriteToFile();
    testCheckID();
    testService();
    testCheckIfItExists();
    testServiceConstructor();
    testDynamicVectorAccess();
    testDynamicVectorAssignmentOperator();
    testDynamicVectorBeginEnd();
}
