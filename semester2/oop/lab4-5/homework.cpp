#include "ui.h"
#include "repository.h"
#include "service.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include "tests.h"
#include <iostream>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    callAllTests();
    //std::cout<<("all tests have passed!");
    std::cout << endl;
    {
       // Service service;
        //Repository basketRepo("basket.txt");
        //Service basketService(basketRepo);
        //UI ui(service, basketService);
        //ui.run();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}