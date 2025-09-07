#include "ui.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "CSVShoppingBasket.h"
#include "HTMLShoppingBasket.h"
#include <algorithm>
#include "Exceptions.h"

std::wstring stringToWstring(const std::string& s)
{
    return std::wstring(s.begin(), s.end());
}

UI::UI(Service& service) :
    service{ service }
{

}

void UI::purchaseMessage()
{
    std::cout << "Thank you for shopping!" << std::endl;
}

void UI::addButton()
{
    std::cout << "***********************" << std::endl;
    std::cout << "******ADD*TO*CART******" << std::endl;
    std::cout << "***********************" << std::endl;
    std::cout << std::endl;
}

void UI::add() {
    std::string size;
    std::string colour;
    std::string str_price;
    int price;
    std::string str_quantity;
    int quantity;
    std::string link;
    std::cout << "Type in the size: ";
    std::cin >> size;
    std::cout << "\nType in the color: ";
    //    std::cin>>color;
    std::cin.ignore();
    getline(std::cin, colour);
    std::cout << "\nType in the price: ";
    std::cin >> str_price;
    std::cout << "\nType in the quantity: ";
    std::cin >> str_quantity;
    std::cout << "\nType in the photograph: ";
    std::cin >> link;
    price = Validator::validate_price_product(str_price);
    quantity = Validator::validate_quantity_product(str_quantity);
    if (!Validator::validate_color_product(colour) || !Validator::validate_size_product(size) || price == -1
        || quantity == -1 || !Validator::validate_photograph_product(link))
        throw ValidatorException("Invalid input!");
    else
    {
        this->service.addService(size, colour, price, quantity, link);
        std::cout << "The product was added successfully!\n";
    }
}

void UI::displayProdAdmin() {

    int count = 0;
    for (const auto& i : this->service.GetRepository())
    {
        std::cout << count + 1 << ")  ""Size: " << i.GetSize() << " Color: " << i.GetColor() << " Price: " << i.GetPrice()
            << " Quantity: " << i.GetQuantity() << "\nLink Photo: "
            << i.GetPhotograph() << "\n" << "\n";
        count++;
    }
}


void UI::updatePrice() {
    std::string size;
    std::string color;
    std::string str_price;
    int price;
    std::string link;
    std::cout << "Type in the size: ";
    std::cin >> size;
    std::cout << "\nType in the color: ";
    std::cin.ignore();
    std::cin >> color;
    std::cout << "\nType in the price: ";
    std::cin >> str_price;
    std::cout << "\nType in the photograph: ";
    std::cin.ignore();
    std::cin >> link;
    price = Validator::validate_price_product(str_price);
    if (!Validator::validate_color_product(color) || !Validator::validate_size_product(size) || price == -1
        || !Validator::validate_photograph_product(link))
        throw ValidatorException("Invalid input!");
    else
    {
        this->service.updatePriceService(size, color, link, price);
        std::cout << "The product was updated successfully!\n";
    }

}

void UI::updateQuantity() {
    std::string size;
    std::string color;
    std::string str_quantity;
    int quantity;
    std::string link;
    std::cout << "Type in the size: ";
    std::cin >> size;
    std::cout << "\nType in the color: ";
    std::cin.ignore();
    std::cin >> color;
    std::cout << "\nType in the quantity: ";
    std::cin >> str_quantity;
    std::cout << "\nType in the photograph: ";
    std::cin.ignore();
    std::cin >> link;
    quantity = Validator::validate_quantity_product(str_quantity);
    if (!Validator::validate_color_product(color) || !Validator::validate_size_product(size) ||
        quantity == -1 || !Validator::validate_photograph_product(link))
        throw ValidatorException("Invalid input!");
    else
    {
        this->service.updateQuantityService(size, color, link, quantity);
        std::cout << "The product was updated successfully!\n";
    }
}

/*
void Console::soldOut() {
    std::string size;
    std::string color;
    std::string photograph;
    std::cout << "Type in the size: ";
    std::cin >> size;
    std::cout << "\nType in the color: ";
    std::cin >> color;
    std::cout << "\nType in the photograph: ";
    std::cin >> photograph;

    if (!Validator::validate_color_product(color) || !Validator::validate_size_product(size) ||
        !Validator::validate_photograph_product(photograph))
        throw ValidatorException("Invalid input!");
    else
    {
        this->service.DeleteService(size, color, photograph, 2);
        std::cout << "The product was deleted successfully!\n";
    }
}*/

void UI::deteleProduct() {
    std::string size;
    std::string color;
    std::string link;
    std::cout << "Type in the size: ";
    std::cin >> size;
    std::cout << "\nType in the color: ";
    std::cin >> color;
    std::cout << "\nType in the photograph: ";
    std::cin >> link;
    if (!Validator::validate_color_product(color) || !Validator::validate_size_product(size) ||
        !Validator::validate_photograph_product(link))
        throw ValidatorException("Invalid input!");
    else
    {
        this->service.deleteService(size, color, link, 1);
        std::cout << "The product was deleted successfully!\n";
    }
}

void UI::adminMenu() {

    std::cout << "Type 1 for adding a product!\n";
    std::cout << "Type 2 for displaying the products!\n";
    std::cout << "Type 3 for deleting a product!\n";
    std::cout << "Type 4 for updating the price of a product!\n";
    std::cout << "Type 5 for updating the quantity of a product!\n";
    std::cout << "Type 0 in order to exit the program!\n";
}

void UI::Admin() {
    bool AM = false;
    adminMenu();
    while (!AM) {
        try {
            std::string command;
            std::cout << "\nCommand> ";
            std::cin >> command;
            if (command != "1" && command != "2" && command != "3" && command != "4" && command != "5" &&
                command != "0")
                std::cout << "Invalid command!\n";
            else
                switch (command[0]) {

                case '1':
                    add();
                    adminMenu();
                    break;

                case '2':
                    displayProdAdmin();
                    adminMenu();
                    break;

                case '3':
                    deteleProduct();
                    adminMenu();
                    break;

                    //case '4':
                      //  soldOut();
                        //break;

                case '4':
                    updatePrice();
                    adminMenu();
                    break;

                case '5':
                    updateQuantity();
                    adminMenu();
                    break;

                case '0':
                    AM = true;
                    break;
                }
        }
        catch (ValidatorException& message)
        {
            std::cout << message.what();
        }
        catch (RepositoryException& message)
        {
            std::cout << message.what();
        }
    }
}

void MenuUserMode()
{
    std::cout << "Type 1 for buying products!\n";
    std::cout << "Type 2 for displaying the shopping basket!\n";
    std::cout << "Type 3 for opening the application!\n";
    std::cout << "Type 0 for exit!\n";
}

int UI::displayProducts() {
    int i = 0;
    if (i < this->service.GetSize())
    {
        std::cout << "Size: " << this->service.GetRepository()[i].GetSize() << " Color: " <<
            this->service.GetRepository()[i].GetColor() << " Price: " << this->service.GetRepository()[i].GetPrice()
            << " Quantity: " << this->service.GetRepository()[i].GetQuantity() << "\nLink Photo: "
            << this->service.GetRepository()[i].GetPhotograph() << "\n" << "\n";
        ShellExecute(nullptr, L"open",
            stringToWstring(this->service.GetRepository()[i].GetPhotograph()).c_str(),
            nullptr, nullptr, SW_SHOWNORMAL);
        std::cout << "1 to buy, 2 for next or 3 to pay\n";
        addButton();
        while (i < this->service.GetSize())
        {
            std::string command;
            std::cout << "\nCommand> ";
            std::cin >> command;
            if (command != "1" && command != "2" && command != "3")
                std::cout << "Invalid command!";
            else
            {
                if (command == "1")
                {
                    this->service.updateQuantityService(this->service.GetRepository()[i].GetSize(),
                        this->service.GetRepository()[i].GetColor(), this->service.GetRepository()[i].GetPhotograph(),
                        this->service.GetRepository()[i].GetQuantity() - 1);

                    if (this->service.GetRepository()[i].GetQuantity() == 0) {
                        this->service.deleteService(service.GetRepository()[i].GetSize(), service.GetRepository()[i].GetColor(), service.GetRepository()[i].GetPhotograph(), 2);
                        std::cout << "Product marked as sold out!\n";
                    }

                    TrenchCoat c(this->service.GetRepository()[i].GetSize(), this->service.GetRepository()[i].GetColor(),
                        this->service.GetRepository()[i].GetPrice(), 1, this->service.GetRepository()[i].GetPhotograph());
                    if (this->service.addUserService(this->service.GetRepository()[i], c) == 1)
                        std::cout << "1 to buy, 2 for next or 3 to pay\n";
                }
                if (command == "2")
                {
                    i++;
                    if (i >= this->service.GetSize()) {
                        i = 0;
                    }
                    if (i < this->service.GetSize()) {
                        std::cout << "Size: " << this->service.GetRepository()[i].GetSize() << " Color: " <<
                            this->service.GetRepository()[i].GetColor() << " Price: "
                            << this->service.GetRepository()[i].GetPrice()
                            << " Quantity: " << this->service.GetRepository()[i].GetQuantity() << "\nLink Photo: "
                            << this->service.GetRepository()[i].GetPhotograph() << "\n" << "\n";
                        ShellExecute(nullptr, L"open",
                            stringToWstring(this->service.GetRepository()[i].GetPhotograph()).c_str(),
                            nullptr, nullptr, SW_SHOWNORMAL);
                        std::cout << "1 to buy, 2 for next or 3 to pay\n";
                        addButton();
                    }
                    else
                        return 0;
                }
                if (command == "3")
                {
                    purchaseMessage();
                    return -1;
                }
            }
        }
    }
    return 1;
}

int UI::filterSize(const std::string& size) {
    int i = 0;
    std::vector<TrenchCoat> elements(this->service.GetRepository().size());
    auto it = copy_if(this->service.GetRepository().begin(), this->service.GetRepository().end(), elements.begin(),
        [size](const TrenchCoat& coat) { return coat.GetSize() == size; });
    elements.resize(it - elements.begin());
    int size1 = elements.size();
    if (!elements.empty())
    {
        if (i < elements.size())
        {
            std::cout << "Size: " << elements[i].GetSize() << " Color: " << elements[i].GetColor() << " Price: "
                << elements[i].GetPrice()
                << " Quantity: " << elements[i].GetQuantity() << "\nLink Photo: "
                << elements[i].GetPhotograph() << "\n" << "\n";
            ShellExecute(NULL, L"open",
                stringToWstring(elements[i].GetPhotograph()).c_str(),
                NULL, NULL, SW_SHOWNORMAL);
            std::cout << "1 to buy, 2 for next or 3 to pay\n";
            addButton();
            while (i < elements.size()) {

                std::string command;
                std::cout << "\nCommand> ";
                std::cin >> command;
                if (command != "1" && command != "2" && command != "3")
                    std::cout << "Invalid command!";
                else {
                    if (command == "1") {
                        int new_quantity = elements[i].GetQuantity() - 1;
                        this->service.updateQuantityService(elements[i].GetSize(),
                            elements[i].GetColor(),
                            elements[i].GetPhotograph(),
                            new_quantity);
                        elements[i].SetQuantity(new_quantity);
                        TrenchCoat c(elements[i].GetSize(),
                            elements[i].GetColor(),
                            elements[i].GetPrice(), 1,
                            elements[i].GetPhotograph());
                        if (this->service.addUserService(elements[i], c) == 1)
                            elements.erase(elements.begin() + i);
                        std::cout << "1 to buy, 2 for next or 3 to pay\n";
                    }
                    if (command == "2") {
                        i++;
                        if (i >= this->service.GetSize()) {
                            i = 0;
                        }
                        if (i < elements.size())
                        {
                            std::cout << "Size: " << elements[i].GetSize() << " Color: " <<
                                elements[i].GetColor() << " Price: "
                                << elements[i].GetPrice()
                                << " Quantity: " << elements[i].GetQuantity()
                                << "\nLink Photo: "
                                << elements[i].GetPhotograph() << "\n" << "\n";
                            ShellExecute(nullptr, L"open",
                                stringToWstring(elements[i].GetPhotograph()).c_str(),
                                nullptr, nullptr, SW_SHOWNORMAL);
                            std::cout << "1 to buy, 2 for next or 3 to pay\n";
                            addButton();
                        }
                        else
                            return 0;
                    }
                    if (command == "3") {
                        purchaseMessage();
                        return -1;
                    }
                }
            }
        }
        return 1;
    }
    return 2;
}

void UI::displayProdUser() {
    std::string size;
    int done = 0;
    if (this->service.GetSize() == 0)
        std::cout << "There are no products on stock!";
    else {
        std::cout << "Type in the size: ";
        std::cin.ignore();
        getline(std::cin, size);
        if (size != "XS" && size != "S" && size != "M" && size != "L" && size != "XL" && !size.empty() && size != "XXL") {
            std::cout << "Invalid size!";
        }
        else {
            while (done == 0) {
                if (size.empty())
                    done = displayProducts();
                else
                    done = filterSize(size);
            }

            if (done == 1)
                throw RepositoryException("There are no products left on stock!");
            else if (done == 2)
                throw RepositoryException("There are no products with the given size!");
        }
    }
    this->basket->data(this->service.GetUserRepository());
    this->basket->write();
}

void UI::displayBasket() {
    int count = 0;
    for (auto i : this->service.GetUserRepository()) {
        std::cout << count + 1 << ")  ""Size: " << i.GetSize() << " Color: " << i.GetColor() << " Price: "
            << i.GetPrice() << " Quantity: " << i.GetQuantity() << "\nLink Photo: "
            << i.GetPhotograph() << "\n" << "\n";
        count++;
    }
    std::cout << "Total price of the items: " << this->service.GetTotalPrice() << '\n';
}

void UI::run()
{
    this->basket->data(this->service.GetUserRepository());
    this->basket->write();
    this->basket->open();
}

void UI::User() {
    bool UM = false;

    while (!UM)
    {
        try {
            std::string command;
            std::cout << '\n';
            MenuUserMode();
            std::cout << '\n';
            std::cin >> command;
            if (command != "1" && command != "2" && command != "3" && command != "0")
                std::cout << "Invalid command!\n";
            else
                switch (command[0]) {

                case '1':
                    displayProdUser();
                    break;
                case '2':
                    displayBasket();
                    break;

                case '3':
                    run();
                    break;

                case '0':
                    UM = true;
                    break;
                }
        }
        catch (RepositoryException& message)
        {
            std::cout << message.what();
        }
    }
}


void UI::start() {

    bool ok = false;
    bool file = false;
    while (!file)
    {
        std::string fileType;
        std::cout << "Type 1 for CSV file or type 2 for HTML file: ";
        std::cin >> fileType;
        if (fileType != "1" && fileType != "2")
            std::cout << "Invalid file type!";
        else
            switch (fileType[0])
            {
            case '1':
                this->basket = new CSVShoppingBasket();
                file = true;
                break;
            case '2':
                this->basket = new HTMLShoppingBasket();
                file = true;
                break;
            }
    }
    while (!ok)
    {
        try {
            std::string command;
            std::cout << "Type 1 for Administrator Mode or type 2 for User Mode or 0 to exit:  ";
            std::cin >> command;
            std::cout << '\n';
            if (command != "1" && command != "2" && command != "0")
                std::cout << "Invalid command!\n";
            else
                switch (command[0]) {
                case '1':
                    Admin();
                    break;

                case '2':
                    User();
                    break;


                case '0':
                    ok = true;
                    delete this->basket;
                    break;
                }
        }
        catch (ValidatorException)
        {

        }
    }
}

