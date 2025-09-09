#include "ui.h"

UI::UI(Service& service) : service(service)
{

}

UI::~UI()
{
}

void UI::run()
{
	while (true) {
		std::cout << "1. Add Assignment\n2. Display Assignments\n3. Disonesty check\n0. Exit\nChoose:";
		int choice;
		std::cin >> choice;
		if (choice == 0) break;
		if (choice == 1) {
			int id;
			std::string name, solution;
			std::cout << "id:";
			std::cin >> id;
			std::cin.ignore();
			std::cout << "name: ";
			getline(std::cin, name);//!!!!! formatul
			std::cout << "solution: ";
			getline(std::cin, solution);

			if (service.addService(id, name, solution)) {
				std::cout << "success\n";
			}
			else {
				std::cout << "fail\n";
			}

			

		}
		if (choice == 2) {
			DynamicVector<Assignment> assignments = service.getAllService();
			for (int i = 0; i < assignments.getSize(); i++) {
				std::cout << assignments[i].getId() << " "
					<< assignments[i].getName() << ": "
					<< assignments[i].getSolution() << "\n";
			}
		}
		if (choice == 3) {
			DynamicVector<std::string> results = service.checkDishonestyService();
			for (int i = 0; i < results.getSize(); i++) {
				std::cout << results[i] << std::endl;
			}
		}
	}
}
