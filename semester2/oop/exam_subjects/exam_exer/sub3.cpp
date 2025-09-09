#include "sub3.h"
/*
int runApp()
{
    MenuBar bar;

    // Actions
    auto* createCpp = new CreateAction("C++");
    auto* createText = new CreateAction("Text");
    auto* exitAction = new ExitAction("Exit");

    // Menus
    auto* cpp = new Menu("C++");
    cpp->add(createCpp);

    auto* text = new Menu("Text");
    text->add(createText);

    auto* newMenu = new Menu("New");
    newMenu->add(text).add(cpp);

    auto* exitMenu = new Menu("Exit");
    exitMenu->add(exitAction);

    auto* fileMenu = new Menu("File");
    fileMenu->add(newMenu).add(exitMenu);

    auto* aboutMenu = new Menu("About");

    bar.add(fileMenu).add(aboutMenu);

    // Print the full menu bar
    cout << bar.print() << endl;

    // Simulate clicks: File -> New -> C++ -> Exit
    cout << "--- Simulating Clicks ---\n";
    fileMenu->clicked();
    newMenu->clicked();
    cpp->clicked();
    createCpp->clicked(); // Execute action

    exitMenu->clicked();
    exitAction->clicked(); // Execute action

    return 0;
}*/

/*
Dacă Action nu ar moșteni MenuItem, atunci fileMenu->add(...) nu ar putea
accepta acțiunea, pentru că lista vector<MenuItem*> items; din Menu acceptă 
doar MenuItem*.
*/
