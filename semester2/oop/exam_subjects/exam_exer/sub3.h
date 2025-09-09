#include <iostream>
#include <string>
#include <vector>
using namespace std;
//COMPOSITE DESIGN PATTERN
/*
Menu este un container (compozit) – poate conține alte MenuItem-uri (submeniu sau acțiune).

Action este un frunză (leaf) – reprezintă acțiunea finală.

MenuItem este interfața comună (baza abstractă) pentru toate elementele din meniu (fie că sunt meniuri sau acțiuni).
*/
// Interface
/*
class MenuItem {
public:
    virtual string print(int indent = 0) const = 0;
    virtual void clicked() = 0;
    virtual ~MenuItem() = default;
};

// Action base class
class Action : public MenuItem {
protected:
    string text;
public:
    Action(const string& t) : text(t) {}
    string print(int indent = 0) const override {
        return string(indent, ' ') + text + "\n";
    }
};

// Specific Actions
class CreateAction : public Action {
public:
    CreateAction(const string& t = "Create") : Action(t) {}
    void clicked() override {
        cout << "Create file" << endl;
    }
};

class ExitAction : public Action {
public:
    ExitAction(const string& t = "Exit") : Action(t) {}
    void clicked() override {
        cout << "Exit application" << endl;
    }
};

// Menu (Composite)
class Menu : public MenuItem {
private:
    string text;
    vector<MenuItem*> items;
public:
    Menu(const string& t) : text(t) {}

    Menu& add(MenuItem* item) {
        items.push_back(item);
        return *this;
    }

    string print(int indent = 0) const override {
        string result = string(indent, ' ') + text + ":\n";
        for (const auto& item : items)
            result += item->print(indent + 2);
        return result;
    }

    void clicked() override {
        cout << "Opened menu: " << text << endl;
    }

    MenuItem* getItem(const string& label) {
        for (auto item : items) {
            if (item->print(0).find(label) != string::npos)
                return item;
        }
        throw runtime_error("Item not found: " + label);
    }

    ~Menu() {
        for (auto item : items)
            delete item;
    }
};

// MenuBar
class MenuBar {
private:
    vector<Menu*> menus;
public:
    MenuBar& add(Menu* m) {
        menus.push_back(m);
        return *this;
    }

    string print() const {
        string result = "Menu Bar:\n";
        for (const auto& m : menus)
            result += m->print(2);
        return result;
    }

    Menu* getMenu(const string& label) {
        for (auto m : menus) {
            if (m->print(0).find(label) != string::npos)
                return m;
        }
        throw runtime_error("Menu not found: " + label);
    }

    ~MenuBar() {
        for (auto m : menus)
            delete m;
    }
};

int runApp();*/