#pragma once
#include "Domain.h"
#include <fstream>
#include <sstream>
#include <vector>

class Repository
{
private:
	vector<User> users;
	vector<Question> questions;
	vector<Answer> answers;
public:
	void loadUsers();
	void loadQuestions();
	void loadAnswers();
	Repository() {
		loadAnswers();
		loadQuestions();
		loadUsers();
	}
	void saveQuestions();
	void saveAnswers();
	~Repository() {
		saveAnswers();
		saveQuestions();
	}
	vector<User>& getUsers() { return this->users; }
	vector<Question>& getQuestions() { return this->questions; };
	vector<Answer>& getAnswers() { return this->answers; };
	void addQuestion(Question& q) {
		questions.emplace_back(q);
	}
	void addAnswer(Answer& ans) {
		answers.emplace_back(ans);
	}
	vector<Answer> getAnswersForQuestion(Question& q) {
		vector<Answer> a;
		for (auto ans : answers) {
			if (q.getId() == ans.getIdQuestion()) {
				a.emplace_back(ans);
			}
		}
		return a;
	}
};

