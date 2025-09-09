#include "GUI.h"
#include <set>

GUI::GUI(Session& session, int userId, QWidget* parent):QWidget(parent),session(session),userId(userId)
{
	session.registerObserver(this);	//!!!!!!!!!!!
	auto users = session.getUsers();
	auto user = find_if(users.begin(), users.end(),
		[userId](User& user) {return user.getId() == userId; });
	setWindowTitle(QString::fromStdString(user->getName()));
	QVBoxLayout* layout = new QVBoxLayout(this);
	QLabel* label = new QLabel("items", this);
	layout->addWidget(label);
    itemsList = new QListWidget(this);

    layout->addWidget(itemsList);

    comboBox = new QComboBox(this);
    layout->addWidget(comboBox);
    auto items = session.getItems();
    set<string> categories;
    for (auto& item : items) {
        categories.insert(item.getCategory());
    }

    comboBox->addItem("All");
    for (auto& category : categories) {
        comboBox->addItem(QString::fromStdString(category));
    }

    if (user->getType() == "admin") {
        auto hlayout = new QHBoxLayout();

        auto nameL = new QLabel("Name:", this);
        nameEdit = new QLineEdit(this);

        auto categoryL = new QLabel("Category:", this);
        categoryEdit = new QLineEdit(this);

        auto priceL = new QLabel("Price:", this);
        priceEdit = new QLineEdit(this);

        hlayout->addWidget(nameL);
        hlayout->addWidget(nameEdit);
        hlayout->addWidget(categoryL);
        hlayout->addWidget(categoryEdit);
        hlayout->addWidget(priceL);
        hlayout->addWidget(priceEdit);

        layout->addLayout(hlayout);
        addButton = new QPushButton("Add");
        layout->addWidget(addButton);

        QObject::connect(addButton, &QPushButton::clicked, this, &GUI::addItem);
    }
    else {
        auto offerL = new QLabel("Offer:", this);
        offerEdit = new QLineEdit(this);
        layout->addWidget(offerL);
        layout->addWidget(offerEdit);

        auto offerButton = new QPushButton("Offer");
        layout->addWidget(offerButton);

        QObject::connect(offerButton, &QPushButton::clicked, [this, &session]() {
            auto row = itemsList->currentRow();
            if (row < 0) {
                return;
            }

            auto items = session.getItems();
            sort(items.begin(), items.end(), [](Item& a, Item& b) {
                return a.getPrice() < b.getPrice();
                });
            auto item = items[row];
            try {
                if (offerEdit->text().isEmpty()) {
                    throw runtime_error("Invalid offer");
                }
                int price = offerEdit->text().toInt();
                if (price < item.getPrice()) {
                    throw runtime_error("Invalid offer");
                }

                session.setPrice(row, price);
                offerEdit->clear();
            }
            catch (runtime_error& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
            });
    }

    offersList = new QListWidget(this);

    layout->addWidget(offersList);

    update();

    setLayout(layout);

    QObject::connect(comboBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged), this,
        &GUI::update);

    QObject::connect(itemsList, &QListWidget::itemSelectionChanged, this,
        &GUI::selectItem);
}

void GUI::update() const
{
    itemsList->clear();
    auto items = session.getItems();

    sort(items.begin(), items.end(), [](Item& a,Item& b) {
        return a.getPrice() < b.getPrice();
        });
    for (auto& item : items) {
        if (item.getCategory() == comboBox->currentText().toStdString() ||
            comboBox->currentText().toStdString() == "All") {
            itemsList->addItem(QString::fromStdString(item.toString()));
        }
    }
}

void GUI::addItem() {
    auto name = nameEdit->text().toStdString();
    auto cateogry = categoryEdit->text().toStdString();
    auto price = priceEdit->text().toStdString();

    try {
        if (name.empty() || cateogry.empty() || price.empty()) {
            throw runtime_error("Invalid item");
        }
        session.addItem(name, cateogry, stoi(price));

        nameEdit->clear();
        categoryEdit->clear();
        priceEdit->clear();

    }
    catch (runtime_error& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}


void GUI::selectItem()
{
    auto row = itemsList->currentRow();
    std::cout << row << std::endl;
    if (row < 0) {
        return;
    }

    auto items = session.getItems();
    sort(items.begin(), items.end(), [](Item& a, Item& b) {
        return a.getPrice() < b.getPrice();
        });
    auto item = items[row];
    offersList->clear();
    for (const auto& offer : item.getOffers()) {
        offersList->addItem(QString::fromStdString(to_string(get<0>(offer)) +
            " , " + get<1>(offer) + " , " +
            to_string(get<2>(offer))));
    }
}
