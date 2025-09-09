#include "Session.h"
#include <algorithm>
#include <unordered_map>

vector<Question> Session::getQuestions()
{
    vector<Question> quest = repo.getQuestions();
    vector<Answer> ans = repo.getAnswers();
    unordered_map<int, int> answerCount;
    for (auto& a : ans) {
        answerCount[a.getIdQuestion()]++;
    }
    sort(quest.begin(), quest.end(), [&](Question& q1, Question& q2) {
        return answerCount[q1.getId()] > answerCount[q2.getId()];
        });
    return quest;
}

void Session::updateAnswerVotes(int answerId, int newVotes) {
    for (auto& ans : repo.getAnswers()) {
        if (ans.getId() == answerId) {
            ans.setVotes(newVotes);
            notify();  
            return;
        }
    }
}

