#include "sub3version2.h"
int runApp2() {
    // Actions
    Action* create = new CreateAction();
    Action* exit = new ExitAction();

    // Menu structure
    MenuItem* cpp = new MenuItem("C++", new CreateAction());
    MenuItem* text = new MenuItem("Text", new CreateAction());

    MenuItem* newItem = new MenuItem("New");
    newItem->add(text);
    newItem->add(cpp);

    MenuItem* exitItem = new MenuItem("Exit", new ExitAction());

    Menu* file = new Menu("File");
    file->add(newItem);
    file->add(exitItem);

    Menu* about = new Menu("About");

    MenuBar bar;
    bar.add(file);
    bar.add(about);

    // Print menubar
    bar.print();

    // Simulate clicking File -> New -> C++
    cout << "\n--- Click: File -> New -> C++ ---\n";
    newItem->clicked();  // Shows Text and C++
    cpp->clicked();      // Executes create

    // Simulate clicking Exit
    cout << "\n--- Click: Exit ---\n";
    exitItem->clicked(); // Executes exit

    return 0;
}
