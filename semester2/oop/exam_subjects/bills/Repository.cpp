#include "Repository.h"

void Repository::load()
{
	ifstream fin(R"(D:\desktop2\teste_oop\test3_model\bills.txt)");
	string line, name, code, sumString, paid;
	double sum;
	bool isPaid;
	const char delimiter = ';';
	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, name, delimiter);
		getline(iss, code, delimiter);
		getline(iss, sumString, delimiter);
		getline(iss, paid, delimiter);
		sum = stod(sumString);
		isPaid = paid == "false" ? false : true;
		this->bills.push_back(Bill(name, code, sum, isPaid));
		cout << this->bills.back().toString() << "\n";
	}
}
