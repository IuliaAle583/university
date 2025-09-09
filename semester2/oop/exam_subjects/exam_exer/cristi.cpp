//aici fac ex 2
#include <iostream>
#include "cristi.h"
using namespace std;
class A {
	int* x;
public:
	static int noOfInstances;
	A(int _x = 0) {
		//_x este doar o conventie de denumire
		// ca sa nu incurce parametrul cu int-ul de la private
		//face asa
		//pot sa fac this->x=new int{x} si e acelasi lucru
		//sauu mai poate si prefixat membrul asa
		//int* m_x
		// m_x = new int{ x };
		x = new int{ _x };
		noOfInstances++;
	}
	int get() {
		return *x;
	}
	void set(int _x) {
		*x = _x;
	}
	~A() { delete x; }
	/*
	for a3 to work i need
	A(const A& other) {
		x = new int{ *other.x };
		noOfInstances++;
	}

	*/
};
int A::noOfInstances = 0;
int runA() {
	A a1, a2;
	//i get 2 instances for both
	//the constructor is called 2 times, both allocating one int on the heap
	// and incrementing on of instances !!!global
	cout << a1.noOfInstances << " ";
	//A a3 = a1; error bc i do not have the rigth method for it
	cout << A::noOfInstances << " ";
	a1.set(8);
	cout << a1.get() << " ";	//8
	cout << a2.get() << " ";	//0
	//cout << a3.get() << " ";
	return 0;
}

class B {
public:
	B() {};
	B(const B&) { cout << "copy"; }
	virtual B f() { 
		cout << "B.f";
		return *this;
	}
	virtual ~B() {
		cout << "~B";
	}
};

class D :public B {
private:
	B* b;
public:
	D(B* _b) : b{ _b } { cout << "D "; }
	B f() override { 
		cout << "D.f ";
		return b->f();
	}
};

int runB() {
	B* b = new B();	//nimic
	B* d = new D{ b }; // D
	d->f(); //D.f B.fcopy~B~B~B
	//pt ca returnez *this in B.f() ma duc in constructor
	// si ii face copie => afiseaza copy
	//sterge copia +? ~B

	delete d;	//destructorul lui B este virtual
	//deci apeleaza ~D() - implict si dupa ~B()
	//cum nu am destructor la D apeleaza direct pe ala de la B
	//=>~B
	delete b;	//~B
	return 0;
}