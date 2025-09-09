#pragma once
#include "Session.h"
#include "Observer.h"
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

class GUI:public QWidget, public Observer
{
	Q_OBJECT;
private:
	Session& session;
	string userName;
	QListWidget* questionList, *answerList;
	QSpinBox* voteSpinBox;
	QLineEdit* questionInput, * answerInput;
	QPushButton* addQuestionButton, * addAnswerButton;
	QLabel* selectedQuestionLabel;
	QPushButton* applyVoteButton;


	void initGUI();
	void connectSignals();
	void reloadQuestions();
	void reloadAnswers(int questionId);
	void update() override;
public slots:
	void handleQuestionSelection();
	void handleAddQuestion();
	void handleAddAnswer();
	void handleVoteChanged();
	void handleAnswerSelection();
	void handleApplyVote();
public:
	~GUI() = default;
	GUI(Session& session,const string& userName, QWidget* parent = nullptr);
};

