#pragma once
#include <iostream>
using namespace std;
//2023-06-16
class Base {
private:
	virtual void f() {
		cout << "Base\n";
	}
public:
	virtual ~Base() {
		f();
	}
	void g() {
		f();
	}
};
class Derived : public Base {
private:
	void f() {
		cout << "Derivced\n";
	}
public:
	void h() {
		Base::g();
		cout << "Function h\n";
	}
	~Derived() {
		f();
	}
};

int runa();

//b
class Exception1 {
public:
	Exception1() { cout << "Exception1 "; }
	virtual void fct() { cout << "Ex1"; }
	virtual ~Exception1() { cout << "~Exception1 "; }
};

class Exception2 :public Exception1 {
public:
	void fct() override { cout << "Ex2 "; }
	virtual ~Exception2() { cout << "~Exceptions"; }
};

string f(int x);

int runb();

//d
/*
int main(){
	vector<string> v{"rain","in","spain","falls","mainly","plain"};
	sort(v.begin(),v.end(),[](string a, string b){return a>b;});
	vector<string>::iterator it=v.begin()+4;
	*it="brain";
	it=v.begin();
	while(it!=v.end()){
		string aux=*it;
		char c1=aux[aux.size()-3];
		char c2=aux[aux.size()-2];
		char c3=aux[aux.size()-1];
		if(c1=='a'&&c2=='i'&&c3=='n')
			cout<<*it<<"\n";
		it++;
	}
	return 0;
}
*/