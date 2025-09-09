#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Action {
public:
    virtual void execute() = 0;
    virtual ~Action() = default;
};

class CreateAction : public Action {
public:
    void execute() override {
        cout << "Create file\n";
    }
};

class ExitAction : public Action {
public:
    void execute() override {
        cout << "Exit application\n";
    }
};

class MenuItem {
private:
    string text;
    Action* action;
    vector<MenuItem*> subitems;

public:
    MenuItem(const string& t, Action* a = nullptr) : text(t), action(a) {}

    void add(MenuItem* m) {
        subitems.push_back(m);
    }

    string print(int indent = 0) const {
        string pad(indent, ' ');
        string output = pad + text + "\n";
        for (auto item : subitems)
            output += item->print(indent + 2);
        return output;
    }

    void clicked() {
        cout << text << " clicked\n";
        if (action)
            action->execute();
        for (auto item : subitems)
            cout << item->print(2);  // display submenus if any
    }

    ~MenuItem() {
        for (auto item : subitems)
            delete item;
        delete action;
    }
};

class Menu {
private:
    string name;
    vector<MenuItem*> items;

public:
    Menu(const string& n) : name(n) {}

    void add(MenuItem* m) {
        items.push_back(m);
    }

    string print() const {
        string output = "Menu: " + name + "\n";
        for (auto item : items)
            output += item->print(2);
        return output;
    }

    const vector<MenuItem*>& getItems() const {
        return items;
    }

    ~Menu() {
        for (auto item : items)
            delete item;
    }
};

class MenuBar {
private:
    vector<Menu*> menus;

public:
    void add(Menu* m) {
        menus.push_back(m);
    }

    void print() const {
        for (auto m : menus)
            cout << m->print();
    }

    ~MenuBar() {
        for (auto m : menus)
            delete m;
    }
};

int runApp2();
