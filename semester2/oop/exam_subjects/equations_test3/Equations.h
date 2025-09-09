#pragma once
#include <string>
using namespace std;
class Equations
{
private:
	double a, b, c;
public:
	Equations(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {};
	~Equations() = default;
	double getA() const { return this->a; };
	double getB() const { return this->b; };
	double getC() const { return this->c; };
	double getDiscriminant() const { return b * b - 4 * a * c; };
	string toString() const {
		string result;
		if (a != 0) {
			result += (a > 0 ? "+" : "-") + to_string(a) + "X^2";
		}
		if (b != 0) {
			result += (b > 0 ? "+" : "-") + to_string(b) + "X";
		}
		if (c != 0) {
			result += (c > 0 ? "+" : "-") + to_string(c);
		}
		return result;
	}
	void SetA(double a) { this->a = a; };
	void setB(double b) { this->b = b; };
	void setC(double c) { this->c = c; };
	string solve() const;
	bool hasRealRoots() const { return this->getDiscriminant() > 0; };
};

