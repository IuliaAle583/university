#include "Repository.h"

void Repository::loadUsers()
{
	ifstream fin(R"(D:\desktop2\teste_oop\exam4\users.txt)");
	string name;
	while (getline(fin, name)) {
		users.emplace_back(name);
	}
	fin.close();
}

void Repository::loadQuestions()
{
	ifstream fin(R"(D:\desktop2\teste_oop\exam4\questions.txt)");
	string name, text,id;
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, id, ',');
		getline(iss, text, ',');
		getline(iss, name);
		questions.emplace_back(stoi(id), name, text);
	}
	fin.close();
}

void Repository::loadAnswers()
{
	ifstream fin(R"(D:\desktop2\teste_oop\exam4\answers.txt)");
	string id, idQ, name, text, votes;
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, id, ',');
		getline(iss, idQ, ',');
		getline(iss, name, ',');
		getline(iss, text, ',');
		getline(iss, votes);
		answers.emplace_back(stoi(id), stoi(idQ), stoi(votes), name, text);

	}
	fin.close();
}

void Repository::saveQuestions()
{
	ofstream fout(R"(D:\desktop2\teste_oop\exam4\questions.txt)");
	for (auto& q : questions) {
		fout << q.getId() << "," << q.getText() << "," << q.getName() << "\n";
	}
	fout.close();
}

void Repository::saveAnswers()
{
	ofstream fout(R"(D:\desktop2\teste_oop\exam4\answers.txt)");
	for (auto& a : answers) {
		fout << a.getId() << "," << a.getIdQuestion() << ","
			<< a.getName() << "," << a.getText() << ","
			<< a.getNrVotes() << "\n";
	}
	fout.close();
}
