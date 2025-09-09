#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Domain
{
	string name, content;
	vector<string> keywords;
public:
	Domain(string name , string content, vector<string> keywords) : name(name), content(content), keywords(keywords) {};
	Domain() = default;
	~Domain() = default;
	string getName() { return this->name; };
	string getContent() { return this->content; };
	vector<string> getKeywords() { return this->keywords; };
	string toString();
	Domain& operator=(const Domain& other) = default;
};

