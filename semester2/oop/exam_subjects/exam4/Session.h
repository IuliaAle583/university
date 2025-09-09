#pragma once
#include "Observer.h"
#include "Subject.h"
#include "Repository.h"
class Session:public Subject
{
private:
	Repository& repo;
public:
	Session(Repository& repo):repo(repo){}
	vector<User> getUsers() { return repo.getUsers(); }
	vector<Answer> getAnswers() { return repo.getAnswers(); }
	vector<Question> getQuestions();
	vector<Answer> getAnswersForQuestion( Question& q) { return repo.getAnswersForQuestion(q); };
	void addQuestion(Question& q) {
		if (q.getText().empty())
			throw runtime_error("Could not add question");
		repo.addQuestion(q);
		notify();
	}
	void addAnswer(Answer& ans) {
		if (ans.getText().empty()) {
			throw runtime_error("Could not add answer");
		}
		repo.addAnswer(ans);
		notify();
	}
	void updateAnswerVotes(int answerId, int newVotes);
};

