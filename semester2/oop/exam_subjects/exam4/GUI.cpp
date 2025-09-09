#include "GUI.h"

void GUI::initGUI()
{
	this->questionList = new QListWidget;
	this->answerList = new QListWidget;

	this->questionInput = new QLineEdit;
	this->addQuestionButton = new QPushButton("Add Question");

	this->answerInput = new QLineEdit;
	this->addAnswerButton = new QPushButton("Add Answer");

	this->voteSpinBox = new QSpinBox;
	voteSpinBox->setRange(0, 10);
	voteSpinBox->setDisabled(true);

	applyVoteButton = new QPushButton("Apply Vote");

	this->selectedQuestionLabel = new QLabel("No question selected");

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(new QLabel(QString::fromStdString(userName)));
	mainLayout->addWidget(questionList);
	mainLayout->addWidget(questionInput);
	mainLayout->addWidget(addQuestionButton);
	mainLayout->addWidget(selectedQuestionLabel);
	mainLayout->addWidget(answerList);
	mainLayout->addWidget(answerInput);
	mainLayout->addWidget(addAnswerButton);
	mainLayout->addWidget(new QLabel("votes: "));
	mainLayout->addWidget(voteSpinBox);
	mainLayout->addWidget(applyVoteButton);

	this->setLayout(mainLayout);
	setWindowTitle(QString::fromStdString(userName));
}

void GUI::connectSignals()
{
	QObject::connect(addQuestionButton, &QPushButton::clicked, this, &GUI::handleAddQuestion);
	QObject::connect(addAnswerButton, &QPushButton::clicked, this, &GUI::handleAddAnswer);
	QObject::connect(questionList, &QListWidget::itemSelectionChanged, this, &GUI::handleQuestionSelection);
	QObject::connect(voteSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &GUI::handleVoteChanged);
	QObject::connect(answerList, &QListWidget::itemSelectionChanged, this, &GUI::handleAnswerSelection);
	QObject::connect(applyVoteButton, &QPushButton::clicked, this, &GUI::handleApplyVote);

}

void GUI::reloadQuestions()
{
	questionList->clear();
	auto questions = session.getQuestions();
	for (auto& q : questions) {
		int count = session.getAnswersForQuestion(q).size();
		QString itemText = QString::fromStdString(q.getText() + " (" + q.getName() + ", Answers: " + std::to_string(count) + " )");
		//este forma textului - cum va aparea in lista
		QListWidgetItem* item = new QListWidgetItem(itemText); //creez un elem nou in lista gui cu textul de mai sus
		item->setData(Qt::UserRole, q.getId());	//ii adaug la element asta - chiar daca textul se schimba, programul stie despre ce este vorba
		/*
		Astfel, păstrezi textul afișat clar și separat stochezi un ID intern care nu este vizibil pentru utilizator, dar important pentru program.
		De exemplu, când utilizatorul dă click pe item, tu poți afla rapid ID-ul întrebării din item->data(Qt::UserRole)
		deci id-ul este ascuns
		Qt::UserRole este rolul rezervat pentru a stoca date personalizate definite de programator. E un fel de "loc special" pentru ca tu să pui
		orice vrei (de obicei un ID, un pointer, o structură etc.).
		*/
		questionList->addItem(item);
	}
}

void GUI::reloadAnswers(int questionId)
{
	answerList->clear();
	for (auto& ans : session.getAnswers()) {
		if (ans.getIdQuestion() == questionId) {
			QString text = QString("%1 | %2 | votes: %3").arg(	//format nume_utilizator | text_raspuns | votes: numar
				//arg(...) înlocuiește %1, %2, %3 cu valorile respective.
				QString::fromStdString(ans.getName()),
				QString::fromStdString(ans.getText()),
				QString::number(ans.getNrVotes()));
			QListWidgetItem* item = new QListWidgetItem(text);
			if (ans.getName() == userName) {
				item->setBackground(Qt::yellow);
				voteSpinBox->setDisabled(true);
			}
			else {
				voteSpinBox->setDisabled(false);
			}
			item->setData(Qt::UserRole, ans.getId());	//Se stochează ID-ul răspunsului în item, la rolul UserRole, ca să poată fi
			//identificat ulterior (ex: pentru votare).
			answerList->addItem(item);
		}
	}
}

void GUI::update()
{
	reloadQuestions();
	if (!questionList->selectedItems().isEmpty()) {
		int questionId = questionList->currentItem()->data(Qt::UserRole).toInt();	//ii ia id-ul ala unic
		reloadAnswers(questionId);	//ii pune raspunsurile lui acolo
		handleAnswerSelection();
	}
}
/*
Aceasta este o funcție de reîmprospătare a interfeței grafice (GUI). Ea:

Reîncarcă lista de întrebări.

Dacă există o întrebare selectată în listă, atunci:

Obține ID-ul întrebării selectate.

Încarcă răspunsurile asociate acestei întrebări.

Apelează o funcție care gestionează selecția unui răspuns.
*/

void GUI::handleAddQuestion()
{
	std::string text = questionInput->text().toStdString();
	if (text.empty()) {
		QMessageBox::warning(this, "warning", "question cannot be empty");
		return;
	}
	int newId = session.getQuestions().size() - 1;	//ii dau un id unic
	Question q(newId, text, userName);
	session.addQuestion(q);
	questionInput->clear();	// sa nu mai apara dupa acolo
}

void GUI::handleAddAnswer()
{
	if (questionList->selectedItems().isEmpty()) return;
	std::string text = answerInput->text().toStdString();
	if (text.empty()) {
		QMessageBox::warning(this, "warning", "Answer text cannot be empty");
		return;
	}
	int questionId = questionList->currentItem()->data(Qt::UserRole).toInt();	//id-ul ala unic ascuns - pot folosi si ceva ce se vede
	int newId = session.getAnswers().size() - 1;
	Answer a(newId, questionId,0, userName, text);
	session.addAnswer(a);
	answerInput->clear();
}

void GUI::handleQuestionSelection() {
	if (questionList->selectedItems().isEmpty()) return;
	auto selectedItem = questionList->currentItem();
	int questionId = selectedItem->data(Qt::UserRole).toInt();
	selectedQuestionLabel->setText("Selected question ID: " + QString::number(questionId));
	reloadAnswers(questionId);
	voteSpinBox->setValue(0);
	voteSpinBox->setDisabled(true);
}

void GUI::handleVoteChanged()
{
	if (answerList->selectedItems().isEmpty()) return;
	auto selectedItem = answerList->currentItem();
	int answerId = selectedItem->data(Qt::UserRole).toInt();

	for (auto& ans : session.getAnswers()) {
		if (ans.getId() == answerId && ans.getName() != userName) {
			int newVotes = voteSpinBox->value();	//ii ia valoarea ca sa o schimbe
			ans.setVotes(newVotes);
			session.notify();	//pt ca e ceva nou si la adaugare si cacaturi fac in session, aici nu
			break;
		}
	}
}

void GUI::handleAnswerSelection()
{
	if (answerList->selectedItems().isEmpty()) {
		voteSpinBox->setDisabled(true);
		return;
	}
	auto selectedItem = answerList->currentItem();
	int answerId = selectedItem->data(Qt::UserRole).toInt();
	for (auto& ans : session.getAnswers()) {
		if (ans.getId() == answerId) {
			if (ans.getName() == userName) {
				voteSpinBox->setDisabled(true);
			}
			else {
				voteSpinBox->setDisabled(false);
				voteSpinBox->setValue(ans.getNrVotes());
			}
			break;
		}
	}
}

void GUI::handleApplyVote()
{
	if (answerList->selectedItems().isEmpty()) return;

	auto selectedItem = answerList->currentItem();
	int answerId = selectedItem->data(Qt::UserRole).toInt();

	session.updateAnswerVotes(answerId, voteSpinBox->value());
}

GUI::GUI(Session& session, const string& userName, QWidget* parent):
	QWidget(parent),session(session),userName(userName)
{
	this->session.registerObserver(this);	//il pun ca observer
	initGUI();
	connectSignals();
	reloadQuestions();
}



