
#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <vector>
#include <algorithm>

#include "Session.h"

class SearchWindow : public QWidget,public Observer {
    Q_OBJECT
private:
    Session& session;
    std::string userName;

    QLineEdit* searchInput;
    QListWidget* questionList;
    QLabel* bestQuestionLabel;
    QListWidget* topAnswersList;

public:
    SearchWindow(Session& session, std::string userName, QWidget* parent = nullptr)
        : QWidget(parent), session(session), userName(userName) {
        session.registerObserver(this); //il pun ca observer ca sa ii dea update si la asta
        setWindowTitle(QString::fromStdString(userName + " - Search Questions"));

        QVBoxLayout* layout = new QVBoxLayout;

        searchInput = new QLineEdit;
        questionList = new QListWidget;
        bestQuestionLabel = new QLabel("Best match: None");
        topAnswersList = new QListWidget;

        layout->addWidget(new QLabel("Search:"));
        layout->addWidget(searchInput);
        layout->addWidget(new QLabel("Matching questions:"));
        layout->addWidget(questionList);
        layout->addWidget(bestQuestionLabel);
        layout->addWidget(new QLabel("Top 3 answers:"));
        layout->addWidget(topAnswersList);

        setLayout(layout);

        connect(searchInput, &QLineEdit::textChanged, this, &SearchWindow::handleSearch);
        connect(questionList, &QListWidget::itemSelectionChanged, this, &SearchWindow::handleQuestionSelected);

        reloadAllQuestions();
    }

    void reloadAllQuestions() {
        questionList->clear();
        auto questions = session.getQuestions();
        for (auto& q : questions) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(q.getText()));
            item->setData(Qt::UserRole, q.getId());
            questionList->addItem(item);
        }
    }

    int similarityScore(const std::string& s1, const std::string& s2) {
        int score = 0;
        int len = std::min(s1.size(), s2.size());
        for (int i = 0; i < len; ++i) {
            if (s1[i] == s2[i]) score++;
        }
        return score;
    }

public slots:
    void handleSearch(const QString& text) {
        std::string searchText = text.toStdString();
        questionList->clear();
        if (searchText.empty()) {
            bestQuestionLabel->setText("Best match: None");
            topAnswersList->clear();
            reloadAllQuestions();
            return;
        }

        auto questions = session.getQuestions();
        std::vector<std::pair<Question, int>> scoredQuestions;  //pair!!

        for (auto& q : questions) {
            int score = similarityScore(q.getText(), searchText);
            if (score > 0) {
                scoredQuestions.push_back({ q, score });
            }
        }

        if (scoredQuestions.empty()) {
            bestQuestionLabel->setText("Best match: None");
            topAnswersList->clear();
            return;
        }
        std::sort(scoredQuestions.begin(), scoredQuestions.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        for (auto& [q, sc] : scoredQuestions) { //!!!!!!!!
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(q.getText()));
            item->setData(Qt::UserRole, q.getId());
            questionList->addItem(item);
        }
        Question& bestQ = scoredQuestions.front().first;    //iau primul element
        bestQuestionLabel->setText(QString::fromStdString("Best match: " + bestQ.getText()));
        auto answers = session.getAnswersForQuestion(const_cast<Question&>(bestQ));
        std::sort(answers.begin(), answers.end(), [](Answer& a, Answer& b) {
            return a.getNrVotes() > b.getNrVotes();
            });

        topAnswersList->clear();
        for (int i = 0; i < std::min(3, (int)answers.size()); ++i) {    //3 sau mai putine
            auto& ans = answers[i];
            QString ansText = QString("%1 | %2 | votes: %3")
                .arg(QString::fromStdString(ans.getName()),
                    QString::fromStdString(ans.getText()),
                    QString::number(ans.getNrVotes()));

            QListWidgetItem* item = new QListWidgetItem(ansText);
            if (ans.getName() == userName)
                item->setBackground(Qt::yellow);
            topAnswersList->addItem(item);  //le afisez in lista
        }
    }

    void handleQuestionSelected() {
    }

    void update() {
        handleSearch(searchInput->text());  //reface search-ul
    }
};
