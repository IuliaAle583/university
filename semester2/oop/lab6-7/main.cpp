#include "FileRepository.h"
#include "ui.h"
#include "tests.h"

int main(int argc, char* argv[])
{
    FileRepository repo(R"(C:\Users\Iulia\Desktop\teste_oop\incercare2\incercare2\text.txt)");
    Repository UserRepo;
    Service service(repo, UserRepo);
    callAllTests();

    UI console{ service };
    console.start();


}