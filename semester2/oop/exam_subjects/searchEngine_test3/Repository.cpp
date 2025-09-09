#include "Repository.h"
#include <fstream>
#include <sstream>

void Repository::load()
{
	char delimiter = '|', comma = ',';
	string name, content;
	vector<string> keywords;
	ifstream fin(R"(D:\desktop2\teste_oop\searchEngine3\documents.txt)");
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		string keyword_str;
		getline(iss, name, delimiter);
		getline(iss, keyword_str, delimiter);
		getline(iss, content, delimiter);
		istringstream isss(keyword_str);
		string keyword;
		while (getline(isss, keyword, comma)) {
			keywords.push_back(keyword);
		}
		documents.push_back(Domain(name, content, keywords));
		keywords.clear();
	}
}
