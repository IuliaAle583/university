
#include "UI.h"
#include <iostream>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UI ui = UI();
    ui.run();
    return 0;
    _CrtDumpMemoryLeaks();
}


