#pragma once
#include <iostream>
#include <string>
using namespace std;
class User
{
private:
	string name;
public:
	User(string n): name(n){}
	string getName() { return this->name; };
	~User() = default;
};

class Question {
private:
	int id;
	string text, name;
public:
	Question(int id, string name, string text): id(id), name(name), text(text){}
	string getName() { return name; };
	string getText() { return text; };
	int getId() { return id; };
};

class Answer {
private:
	int id, idQuestion, nrVotes;
	string nameUser, text;
public:
	Answer(int id, int idQ, int nrv, string n, string t):
		id(id),idQuestion(idQ),nrVotes(nrv),nameUser(n),text(t){}
	string getName() { return this->nameUser; };
	string getText() { return this->text; };
	int getId() { return this->id; };
	int getIdQuestion() { return this->idQuestion; };
	int getNrVotes() { return this->nrVotes; };
	void setVotes(int votes) { this->nrVotes = votes; };
};
