#include "Repository.h"

void Repository::load()
{
	ifstream fin(R"(D:\desktop2\teste_oop\equations_test3\euqtions.txt)");
	string line;
	string aStr, bStr, cStr;
	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, aStr, ',');
		getline(iss, bStr, ',');
		getline(iss, cStr, ',');
		equations.push_back(Equations(stod(aStr), stod(bStr), stod(cStr)));
	}
}

vector<Equations> Repository::getAll()
{
	return equations;
}

void Repository::addEquation(Equations eq)
{
	this->equations.push_back(eq);
}
