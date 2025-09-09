#include "GUI.h"
#include "WindowMap.h"

Window::Window(Session& session, Driver& driver, QWidget* parent)
    : session(session), driver(driver), QWidget(parent) {
    session.registerObserver(this); //!!!!!!!!!!!!!!!!!! always - il inregistrez la notificari
    setWindowTitle(QString::fromStdString(driver.getName()));
    //deasupra la lista imi apar astea
    auto layout = new QVBoxLayout();
    auto topLayout = new QHBoxLayout();
    location = new QLabel(QString::fromStdString(to_string(driver.getLatitude()) + "-" + to_string(driver.getLongitude())));
    score = new QLabel(QString::fromStdString(to_string(driver.getScore()) + " Stars"));
    topLayout->addWidget(location);
    topLayout->addWidget(score);

    auto listLayout = new QVBoxLayout();
    auto lbl = new QLabel("Reports:");
    //lista cu datele
    list = new QListWidget();
    listLayout->addWidget(lbl);
    listLayout->addWidget(list);
    //tot list layout folosesc si la mesaje
    auto msgLayout = new QVBoxLayout();
    auto msgLbl = new QLabel("Messages:");
    messages = new QListWidget();

    auto msgInputLayout = new QHBoxLayout();
    message = new QLineEdit();
    send = new QPushButton("Send");

    msgInputLayout->addWidget(message);
    msgInputLayout->addWidget(send);

    msgLayout->addWidget(msgLbl);
    msgLayout->addWidget(messages);
    msgLayout->addLayout(msgInputLayout);


    auto llbl = new QLabel("Reports:");
    auto reportLayout = new QHBoxLayout();
    description = new QLabel("Description:");
    lat = new QLabel("Lat:");
    lg = new QLabel("Lg:");

    descriptionInput = new QLineEdit();
    latInput = new QLineEdit();
    lgInput = new QLineEdit();

    auto reportBtn = new QPushButton("Report");

    reportLayout->addWidget(description);
    reportLayout->addWidget(descriptionInput);

    reportLayout->addWidget(lat);
    reportLayout->addWidget(latInput);

    reportLayout->addWidget(lg);
    reportLayout->addWidget(lgInput);

    reportLayout->addWidget(reportBtn);

    viewBtn = new QPushButton("Open Drawing Window");

    layout->addLayout(topLayout);
    layout->addLayout(listLayout);
    layout->addLayout(msgLayout);
    layout->addWidget(llbl);
    layout->addLayout(reportLayout);
    layout->addWidget(viewBtn);

    setLayout(layout);

    update();
    //send message
    connect(send, &QPushButton::clicked, this, &Window::sendMessage);
    //send report
    connect(reportBtn, &QPushButton::clicked, this, &Window::sendReport);
    //validate report by clicking on it in the list!!!!!!!!!
    connect(list, &QListWidget::itemClicked, this, &Window::validateReport);
    //open the map
    connect(viewBtn, &QPushButton::clicked, this, &Window::openWinMap);

};

void Window::update() {
    //AFTER EVERY MODIFICATION THIS IS CALLED BY NOTIFY!!!!!!!!!!!
    //!!!!!!!!! do not forget to clear the list first and rewrite everyting in i
    list->clear();
    //REWIRTE THE LIST 
    for (auto x : session.getInterestReports(driver.getName())) {
        list->addItem(QString::fromStdString(
            x.getDescription() + " / " + x.getReporter() + " / " +
            to_string(x.getLatitude()) + "-" + to_string(x.getLongitude()) + " / " +
            to_string(x.getStatus())));

        if (x.getStatus() == true) {
            list->item(list->count() - 1)->setFont(QFont("Arial", -1, QFont::Bold));    //set the item to bold
        }
    }
    //REWRITE THE MESSAGES
    messages->clear();

    for (auto x : session.getMessage()) {
        messages->addItem(QString::fromStdString(x));

        if (x.find("[" + driver.getName() + "]") != string::npos) {
            messages->item(messages->count() - 1)
                ->setFont(QFont("Arial", -1, QFont::Bold));
        }
    }
    //increase the reporters score with 1
    score->clear();

    if (driver.getName() == "Craig")
        std::cout << driver.getName() << driver.getScore() << std::endl;

    score->setText(
        QString::fromStdString(to_string(driver.getScore()) + " Stars"));
    //REPAINT THE MAP
    repaint();
}

void Window::sendMessage() {
    try {
        session.addMessage(driver.getName(), message->text().toStdString());
    }
    catch (const runtime_error& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Window::sendReport() {
    try {
        auto description = descriptionInput->text().toStdString();
        auto lat = latInput->text().toInt();
        auto lg = lgInput->text().toInt();

        session.addReport(description, driver.getName(), lat, lg, false);
    }
    catch (const runtime_error& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Window::validateReport() {
    try {
        auto selected = list->selectedItems().at(0)->text().toStdString();  //ia primul item selectat din QListWidget
        auto description = selected.substr(0, selected.find(" / "));    //ia doar descrierea raportului
        session.addValidation(description, driver.getName());
    }
    catch (const runtime_error& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Window::openWinMap() {
    auto winMap = new WinMap(session);
    winMap->show();
}