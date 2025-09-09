#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <vector>
using namespace std;
//use inline if it is in the header, otherwise not
//but i am lazy
template <typename T>
class Stack {
private:
    T* data;
    int capacity;
    int top;

public:
    // Inline Constructor
    inline Stack(int maxCapacity) : capacity(maxCapacity), top(0) {
        data = new T[capacity];
    }

    // Inline Copy Constructor
    inline Stack(const Stack& other) : capacity(other.capacity), top(other.top) {
        data = new T[capacity];
        for (int i = 0; i < top; ++i)
            data[i] = other.data[i];
    }

    // Inline Assignment Operator
    inline Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            top = other.top;
            data = new T[capacity];
            for (int i = 0; i < top; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Inline Destructor
    inline ~Stack() {
        delete[] data;
    }

    // Inline Getter for Max Capacity
    inline int getMaxCapacity() const {
        return capacity;
    }

    // Inline Push via Operator+
    inline Stack operator+(const T& element) const {
        //Operatorul creează un nou Stack care este o copie a stack-ului original, adaugă un element
        //în acea copie, și returnează noua versiune.
        //ex de folosire: s = s + "test";
        if (top >= capacity)
            throw std::runtime_error("Stack is full!");
        Stack newStack(*this);
        newStack.data[newStack.top++] = element;
        return newStack;
    }

    // Inline Pop
    inline T pop() {
        if (top == 0)
            throw std::runtime_error("Stack is empty!");
        return data[--top];
    }
};

void testStack() {
    Stack<std::string> s{ 2 };
    assert(s.getMaxCapacity() == 2);
    try {
        s = s + "examination";
        s = s + "oop";
        s = s + "test";
    }
    catch (std::exception& e) {
        assert(strcmp(e.what(), "Stack is full!") == 0);
    }
    assert(s.pop() == "oop");
    assert(s.pop() == "examination");
}



////////////////////////////////////////////
//define classes SmartPointer and Set st the code is correct. Enumarate
//the data members(including types) and the prototipes of all the methods
//and implement the methods allowing the operation shown

template<typename T>
class SmartPointer {
private:
    T* pointer;
public:
    inline SmartPointer(T* pointer):pointer(new T(*pointer)){}
    //fac pointer(new T(*pointer)) ca sa fie deep copy si sa nu se incurce in stiinta
    inline SmartPointer(const SmartPointer& other):pointer(new T(*other.pointer)){}
    inline SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            delete pointer;
            pointer = new T(*other.pointer);
        }
        return *this;
    }
    inline ~SmartPointer() {
        delete pointer;
    }
    inline T& operator*()const {
        return *pointer;
    }
    inline bool operator==(const SmartPointer& other) const {
        return *pointer == *other.pointer;
    }

};

template<typename T>
class Set {
private:
    vector<T> elements;
public:
    inline Set() = default;
    inline Set& operator=(const Set& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }
    inline Set operator+(const T& element) const {
        Set result = *this;
        for (const auto& el : elements) {
            if (el == element)
                throw std::runtime_error("element already exists");
        }
        result.elements.push_back(element);
        return result;
    }
    inline Set& remove(const T& element) {
        for (auto it = elements.begin(); it != elements.end(); it++) {
            if (*it == element) {
                elements.erase(it);
                //asa e la vector, daca dau remove merge cu iteratorul si doar face
                //o copie fara acel element
                break;
            }
        }
        return *this;
    }
    inline typename vector<T>::iterator begin() { return elements.begin(); }
    inline typename vector<T>::iterator end() { return elements.end(); }
    inline typename vector<T>::const_iterator begin() const { return elements.begin(); }
    inline typename vector<T>::const_iterator end() const { return elements.end(); }
};


void function2() {
    SmartPointer<string> s1{ new string{"A"} };
    SmartPointer<string> s2 = s1;
    SmartPointer<string> s3{ new string{"C"} };
    Set<SmartPointer<string>> set1{};
    try {
        set1 = set1 + s1;
        set1 = set1 + s2;
    }
    catch (std::runtime_error& ex) {
        cout << ex.what();  //prints element already exists
    }
    SmartPointer<int> i1{ new int{1} };
    SmartPointer<int> i2{ new int{2} };
    SmartPointer<int> i3{ new int{3} };
    Set<SmartPointer<int>> set2{};
    set2 = set2 + i1;
    set2 = set2 + i2;
    set2 = set2 + i3;
    set2.remove(i1).remove(i3);
    for (auto e : set2)
        cout << *e << ", "; //prints 2,
}


////////////////////////////////////////////////////////////////////////
//define classes Object, Integer, String and MyObjectList st the following
//code is correct and memory is correctly managed. enumarate the data members
//and the prototipes...
class Object {
public:
    virtual ~Object() = default;
    virtual void print() const = 0;

};

class Integer: public Object {
    int value;
public:
    inline Integer(int v) :value(v) {

    }
    inline void print()const override { std::cout << value << ", "; }
};


class String :public Object{
private:
    string value;
public:
    inline String(const char* s): value(s){}
    inline bool operator==(const char* s) const { return value == s; }
    //this one is for s1=="HI"
    //inline bool operator==(const String& other) const { return value == other.value; }
    //the second operator == is for (s1==s2)
    inline void print() const override { cout << value << ", "; }
};



class MyObjectList {
private:
    vector<Object*> elements;
public:
    inline ~MyObjectList() {
        for (auto obj : elements)
            delete obj;
    }
    //so here i return this so i allow function calls like:
    //list.add(new Integer{ 2 }).add(new String{ "HI" });
    //so with chaining
    //each call to add() returns the object itself, so you can imediatelly
    //cal another method on it
    //if i return void i do how it was until now aka
    //list.add(new Integer{2}); and separately list.add(new String{"HI"});
    inline MyObjectList& add(Object* o) {
        elements.push_back(o);
        return *this;
    }
    inline size_t length() const {
        return elements.size();
    }
    inline auto begin() { return elements.begin(); }
    inline auto end() { return elements.end(); }
};

void function() {
    MyObjectList list{};
    list.add(new Integer{ 2 }).add(new String{ "HI" });
    String* s = new String{ "Bye" };
    assert(*s == "Bye");    // i need == operator for comparison
    //for this i need c style checking witg the first operator style
    list.add(s).add(new Integer{ 5 });
    assert(list.length() == 4);
    //prints 2 Hi Bye 5
    for (Object* o : list)
        o->print();
}

//////////////////////////////////////////////////
//define the classes Person and MultiDictionary st the following c++ code is correct
class Person {
private:
    int age;
    string name;
public:
    Person(int age, const string& name): age(age), name(name){}
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.name << " is " << p.age << " years old";
        return os;
    }
    bool operator==(const Person& other) const {
        return age == other.age && name == other.name;
    }
};

template<typename K, typename V>
class MultiDictionary {
private:
    vector<pair<K, V>> entries;
public:
    MultiDictionary() = default;
    MultiDictionary& add(const K& key, const V& value) {
        entries.emplace_back(key, value);
        return *this;
    }
    MultiDictionary& erase(const K& key, const V& value) {
        bool found = false;
        for (auto it = entries.begin(); it != entries.end(); it++) {
            if (it->first == key) {
                found = true;
                //erase the value associated to it
                if (it->second == value) {
                    entries.erase(it);
                    return *this;
                }
            }
        }
        if (!found)
            throw runtime_error("Key does not exist");
        else
            throw runtime_error("Given value does not exist for given key");

    }
    void print(ostream& os) const {
        for (const auto& pair : entries) {
            os << pair.first << " " << pair.second << "; ";
        }
        os << endl;
    }
    size_t sizeForKey(const K& key) const {
        size_t count = 0;
        for (const auto& pair : entries) {
            if (pair.first == key) {
                ++count;
            }
        }
        return count;
    }
};



void function3() {
    MultiDictionary<int, string> d1{};
    d1.add(1, "a").add(2, "b").add(1, "c").add(3, "d");
    d1.print(std::cout); //prints 1 a; 1 c; 2 b; 3 d
    try {
        d1.erase(4, "w");
        assert(false);
    }
    catch (std::runtime_error& e) {
        try {
            assert(strcmp(e.what(), "Key does not exist") == 0);
            d1.erase(2, "w");
            assert(false);
        }
        catch (std::runtime_error& e) {
            assert(strcmp(e.what(), "Given value does not exist for given key") == 0);
        }
    }
    d1.erase(1, "a");
    d1.print(std::cout);    //prints 1 c; 2 b; 3 d
    MultiDictionary<string, Person> d2{};
    Person p1{ 23, "Mircea" };
    Person p2{ 20, "Ioana" };
    cout << p2; //prints Ioana is 20 years old
    d2.add("a", p1).add("a", p2);
    d2.print(std::cout);    //prints a Mircea is 23 years old; a Ioana is 20 years old
    assert(d2.sizeForKey("a") == 2);
    assert(d2.sizeForKey("b") == 0);
}

////////////////////////////////////////////////////////////////
//define the classes SmartPointer1 and Vector
template<typename T>
class SmartPointer1 {
private:
    T* pointer;
public:
    SmartPointer1(T* p): pointer(new T(*p)){}
    SmartPointer1(const SmartPointer1& other): pointer(new T(*other.pointer)){}
    SmartPointer1& operator=(const SmartPointer1& other) {
        if (this != &other) {
            delete pointer;
            pointer = new T(*other.pointer);
            //pt v2=v2....
        }
        return *this;
    }
    T& operator*() const {
        return *pointer;
    }
    bool operator==(const SmartPointer1& other) const {
        return *pointer == *other.pointer;
    }
    ~SmartPointer1() {
        delete pointer;
    }
};

template<typename T>
class Vector {
private:
    vector<T> elems;
public:
    Vector() = default;
    Vector& add(const T& element) {
        elems.push_back(element);
        return *this;
    }
    Vector operator-(const T& element) const {
        Vector result = *this;  //copie
        auto it = find(result.elems.begin(), result.elems.end(), element);
        if (it != result.elems.end()) {
            result.elems.erase(it); //sterg elementul
        }
        else {
            throw runtime_error("Element does not exist");
        }
        return result;
    }
    typename vector<T>::iterator begin() { return elems.begin(); }
    typename vector<T>::iterator end() { return elems.end(); }
    typename vector<T>::const_iterator begin() const { return elems.begin(); }
    typename vector<T>::const_iterator end() const { return elems.end(); }

};

void function4() {
    SmartPointer1<int> i1{ new int{1} };
    SmartPointer1<int> i2{ new int{2} };
    SmartPointer1<int> i3{ new int{3} };
    Vector<SmartPointer1<int>> v1{};
    v1.add(i1).add(i2).add(i3);
    for (auto e : v1)
        cout << *e << ", ";    //prints 1,2,3
    SmartPointer1<string> s1{ new string{"A"} };
    SmartPointer1<string> s2 = s1;
    SmartPointer1<string> s3{ new string {"C"} };
    Vector<SmartPointer1<string>> v2{};
    v2.add(s2).add(s1);
    try {
        v2 = v2 - s2;   //scoate cate un element din vector
        v2 = v2 - s3;
    }
    catch (std::runtime_error& ex) {
        cout << ex.what();  //prints Element does not exist
    }
}