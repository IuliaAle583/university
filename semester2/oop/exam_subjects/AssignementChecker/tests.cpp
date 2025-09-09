#include "tests.h"
#include "repository.h"
#include "service.h"
#include <cassert>

void testAdd() {
    std::string testFileName = "testFile.txt";

    Repository repo(testFileName);

    std::remove(testFileName.c_str());

    repo.add(1, "Assignment1", "Solution1");

    DynamicVector<Assignment> allAssignments = repo.getAll();
    assert(allAssignments.getSize() == 1); 

    assert(allAssignments[0].getId() == 1);
    assert(allAssignments[0].getName() == "Assignment1");
    assert(allAssignments[0].getSolution() == "Solution1");

    std::ifstream fin(testFileName);
    std::string line;
    std::getline(fin, line);
    assert(line == "1 Assignment1,Solution1");

    std::cout << "Testul pentru add a trecut cu succes!" << std::endl;
}

void callAllTests()
{
    testAdd();
}
