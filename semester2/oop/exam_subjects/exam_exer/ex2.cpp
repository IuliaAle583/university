#include "ex2.h"
int runa(){
	Base * b = new Derived{};
	b->g();
	Derived* d = dynamic_cast<Derived*>(b);
	if (d != nullptr)
		d->h();
	delete b;
	return 0;
}

string f(int x)
{
	cout << "Hi ";
	if (x % 2 == 0)
		throw Exception1{};
	else
		throw Exception2{};
	return string{ "Bye " };
}

int runb()
{
	try {
		cout << f(5);
		cout << f(2);
	}
	catch (Exception1& ex) { ex.fct(); }
	catch (Exception2& ex2) { ex2.fct(); }
	return 0;
}


