#include "Repository.h"

void Repository::loadUsers()
{
	ifstream file(R"(D:\desktop2\teste_oop\exam1\exam1\users.txt)");
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string name, type, idstr;
		getline(iss, name, ',');
		getline(iss, idstr, ',');
		getline(iss, type);
		users.emplace_back(User(name, stoi(idstr), type));

	}
	file.close();
}

void Repository::loadItems()
{
	ifstream file(R"(D:\desktop2\teste_oop\exam1\exam1\items.txt)");
	string line;
	vector<tuple<int, string, int>> offersFinal;
	while (getline(file, line)) {
		istringstream iss(line);
		string name, category, priceStr;
		getline(iss, name, ',');
		getline(iss, category, ',');
		getline(iss, priceStr, ',');
		string offers;
		getline(iss, offers);
		istringstream issOff(offers);
		while (getline(issOff, offers, ',')) {
			istringstream of(offers);
			string id, date, price;
			getline(of, id, '|');
			getline(of, date, '|');
			getline(of, price);
			offersFinal.emplace_back(make_tuple(stoi(id), date, stoi(price)));

		}
		//auto it = Item(name, category, stoi(priceStr));
		//for (const auto& offer : offersFinal) {
			//it.addOffer(get<0>(offer), get<1>(offer), get<2>(offer));
		//}
		items.emplace_back(Item(name, category, stoi(priceStr), offersFinal));
		offersFinal.clear();
	}
	file.close();
}

void Repository::saveUsersToFile()
{
	ofstream file(R"(D:\desktop2\teste_oop\exam1\exam1\users.txt)");
	for (auto& user : users) {
		file << user.getName() << ", " << user.getId() << ", " << user.getType() << endl;
	}
	file.close();
}

void Repository::saveItemsToFile()
{
	ofstream file(R"(D:\desktop2\teste_oop\exam1\exam1\items.txt)");
	for (auto& item : items) {
		file << item.getName() << ", " << item.getCategory() << ", " << item.getPrice() << ",";
		for (auto& offer : item.getOffers()) {
			file << get<0>(offer) << "|" << get<1>(offer) << "|" << get<2>(offer) << ",";
		}
		file << endl;
	}
	file.close();
}
