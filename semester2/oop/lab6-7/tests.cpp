#include "tests.h"
#include <cassert>
#include "domain.h"
#include "service.h"
#include "Exceptions.h"
#include "validator.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//domain tests

void testDefaultConstructor() {
    TrenchCoat coat;
    assert(coat.GetSize() == "");
    assert(coat.GetColor() == "");
    assert(coat.GetPrice() == 0);
    assert(coat.GetQuantity() == 0);
    assert(coat.GetPhotograph() == "");
    std::cout << "Default Constructor Test Passed!" << std::endl;
}

void testParameterizedConstructor() {
    TrenchCoat coat("L", "Black", 150, 10, "http://example.com/coat.jpg");
    assert(coat.GetSize() == "L");
    assert(coat.GetColor() == "Black");
    assert(coat.GetPrice() == 150);
    assert(coat.GetQuantity() == 10);
    assert(coat.GetPhotograph() == "http://example.com/coat.jpg");
    std::cout << "Parameterized Constructor Test Passed!" << std::endl;
}

void testSetQuantity() {
    TrenchCoat coat;
    coat.SetQuantity(20);
    assert(coat.GetQuantity() == 20);
    std::cout << "SetQuantity Test Passed!" << std::endl;
}

void testSetPrice() {
    TrenchCoat coat;
    coat.SetPrice(200);
    assert(coat.GetPrice() == 200);
    std::cout << "SetPrice Test Passed!" << std::endl;
}

void testGetSize() {
    TrenchCoat coat("M", "Red", 100, 5, "http://example.com/redcoat.jpg");
    assert(coat.GetSize() == "M");
    std::cout << "GetSize Test Passed!" << std::endl;
}

void testGetColor() {
    TrenchCoat coat("M", "Red", 100, 5, "http://example.com/redcoat.jpg");
    assert(coat.GetColor() == "Red");
    std::cout << "GetColor Test Passed!" << std::endl;
}

void testGetPrice() {
    TrenchCoat coat("M", "Red", 100, 5, "http://example.com/redcoat.jpg");
    assert(coat.GetPrice() == 100);
    std::cout << "GetPrice Test Passed!" << std::endl;
}

void testGetQuantity() {
    TrenchCoat coat("M", "Red", 100, 5, "http://example.com/redcoat.jpg");
    assert(coat.GetQuantity() == 5);
    std::cout << "GetQuantity Test Passed!" << std::endl;
}

void testGetPhotograph() {
    TrenchCoat coat("M", "Red", 100, 5, "http://example.com/redcoat.jpg");
    assert(coat.GetPhotograph() == "http://example.com/redcoat.jpg");
    std::cout << "GetPhotograph Test Passed!" << std::endl;
}

void testTokenize() {
    std::string str = "L,Red,150,5,http://example.com/coat.jpg";
    std::vector<std::string> result = TrenchCoat::tokenize(str, ',');
    assert(result.size() == 5);
    assert(result[0] == "L");
    assert(result[1] == "Red");
    assert(result[2] == "150");
    assert(result[3] == "5");
    assert(result[4] == "http://example.com/coat.jpg");
    std::cout << "Tokenize Test Passed!" << std::endl;
}



void testOperatorAssignment() {
    TrenchCoat coat1("S", "Yellow", 80, 20, "http://example.com/yellowcoat.jpg");
    TrenchCoat coat2 = coat1;
    assert(coat2.GetSize() == "S");
    assert(coat2.GetColor() == "Yellow");
    assert(coat2.GetPrice() == 80);
    assert(coat2.GetQuantity() == 20);
    assert(coat2.GetPhotograph() == "http://example.com/yellowcoat.jpg");
    std::cout << "OperatorAssignment Test Passed!" << std::endl;
}

//repository

void testAddRepo() {
    Repository repo;

    assert(repo.GetSize() == 0);

    repo.AddRepo("L", "Blue", 120, 5, "https://example.com/new-coat.jpg");

    assert(repo.GetSize() == 1);
    assert(repo.getArray().back().GetColor() == "Blue");
    assert(repo.getArray().back().GetSize() == "L");
    std::cout << "AddRepo Test Passed!" << std::endl;
}

void testDeleteRepo() {
    Repository repo;
    assert(repo.GetSize() == 0);
    repo.AddRepo("M", "Blue", 120, 5, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
    repo.deleteRepo("M", "Blue", "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");

    assert(repo.GetSize() == 0);
    assert(repo.Check("M", "Blue", "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg") == -1);
    std::cout << "DeleteRepo Test Passed!" << std::endl;
}

void testSoldOut() {
    Repository repo;
    repo.AddRepo("L", "Grey", 100, 0, "https://example.com/grey-coat.jpg");

    assert(repo.GetSize() == 1);

    repo.soldOut("L", "Grey", "https://example.com/grey-coat.jpg");

    assert(repo.GetSize() == 0);
    assert(repo.Check("L", "Grey", "https://example.com/grey-coat.jpg") == -1);
    std::cout << "SoldOut Test Passed!" << std::endl;
}

void testAddDuplicateRepo() {
    Repository repo;
    repo.AddRepo("M", "Blue", 100, 6, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
    try {
        repo.AddRepo("M", "Blue", 100, 6, "https://www.morganclare.co.uk/images/luxe-blue-coat-p36372-114149_image.jpg");
        std::cout << "Duplicate Add Test Failed!" << std::endl;
    }
    catch (const RepositoryException& e) {
        std::cout << "Duplicate Add Test Passed!" << std::endl;
    }
}

//service

void testAddService() {
    Repository repo;
    Repository userRepo;
    Service service(repo, userRepo);

    assert(service.GetSize() == 0);

    service.addService("L", "Blue", 100, 5, "https://example.com/blue-coat.jpg");

    assert(service.GetSize() == 1);
    assert(service.GetRepository().back().GetColor() == "Blue");
    assert(service.GetRepository().back().GetSize() == "L");
    std::cout << "AddService Test Passed!" << std::endl;
}


void testDeleteService() {
    Repository repo;
    Repository userRepo;
    Service service(repo, userRepo);

    service.addService("M", "Red", 150, 3, "https://example.com/red-coat.jpg");

    assert(service.GetSize() == 1);

    service.deleteService("M", "Red", "https://example.com/red-coat.jpg", 1);

    assert(service.GetSize() == 0);
    std::cout << "DeleteService Test Passed!" << std::endl;
}

void testUpdatePriceService() {
    Repository repo;
    Repository userRepo;
    Service service(repo, userRepo);

    service.addService("L", "Green", 100, 10, "https://example.com/green-coat.jpg");

    assert(service.GetRepository().back().GetPrice() == 100);

    service.updatePriceService("L", "Green", "https://example.com/green-coat.jpg", 120);

    assert(service.GetRepository().back().GetPrice() == 120);
    std::cout << "UpdatePriceService Test Passed!" << std::endl;
}

void testUpdateQuantityService() {
    Repository repo;
    Repository userRepo;
    Service service(repo, userRepo);

    service.addService("S", "Yellow", 150, 3, "https://example.com/yellow-coat.jpg");

    assert(service.GetRepository().back().GetQuantity() == 3);

    service.updateQuantityService("S", "Yellow", "https://example.com/yellow-coat.jpg", 10);

    assert(service.GetRepository().back().GetQuantity() == 10);
    std::cout << "UpdateQuantityService Test Passed!" << std::endl;
}

void testAddUserService() {
    Repository repo;
    Repository userRepo;
    Service service(repo, userRepo);

    service.addService("M", "Pink", 200, 5, "https://example.com/pink-coat.jpg");

    assert(service.GetUserRepository().size() == 0);

    TrenchCoat coat = service.GetRepository().back();
    int status = service.addUserService(coat, coat);

    assert(service.GetUserRepository().size() == 1);
    assert(service.GetUserRepository().back().GetColor() == "Pink");

    assert(service.GetTotalPrice() == 200);

    service.addUserService(coat, coat);
    assert(service.GetTotalPrice() == 400);

    std::cout << "AddUserService Test Passed!" << std::endl;
}

void testGetFilteredRepository() {
    Repository repo;
    Repository userRepo;
    Service service(repo, userRepo);

    service.addService("M", "Blue", 100, 5, "https://example.com/blue-coat.jpg");
    service.addService("L", "Green", 150, 3, "https://example.com/green-coat.jpg");
    service.addService("S", "Red", 200, 10, "https://example.com/red-coat.jpg");

    std::vector<TrenchCoat> filteredCoats = service.GetFilteredRepository("M");

    assert(filteredCoats.size() == 1);
    assert(filteredCoats[0].GetSize() == "M");

    filteredCoats = service.GetFilteredRepository("All sizes");
    assert(filteredCoats.size() == 3);

    std::cout << "GetFilteredRepository Test Passed!" << std::endl;
}

//validator

void testValidateColorProduct() {
    assert(Validator::validate_color_product("Blue") == true);
    assert(Validator::validate_color_product("Green") == true);
    assert(Validator::validate_color_product("123") == false);
    assert(Validator::validate_color_product("Red123") == false);
    std::cout << "ValidateColorProduct Test Passed!" << std::endl;
}

void testValidateSizeProduct() {
    assert(Validator::validate_size_product("S") == true);
    assert(Validator::validate_size_product("M") == true);
    assert(Validator::validate_size_product("XXL") == true);
    assert(Validator::validate_size_product("XXXS") == false);
    assert(Validator::validate_size_product("LARGE") == false);
    std::cout << "ValidateSizeProduct Test Passed!" << std::endl;
}

void testValidatePriceProduct() {
    assert(Validator::validate_price_product("100") == 100);
    assert(Validator::validate_price_product("2") == 2);
    assert(Validator::validate_price_product("abc") == -1);
    assert(Validator::validate_price_product("") == -1);
    std::cout << "ValidatePriceProduct Test Passed!" << std::endl;
}

void testValidatePhotographProduct() {
    assert(Validator::validate_photograph_product("https://example.com/photo.jpg") == true);
    assert(Validator::validate_photograph_product("https://example.com/photo.com") == true);
    assert(Validator::validate_photograph_product("htps://example/photo.jpg") == false);
    assert(Validator::validate_photograph_product("example.jpg") == false);
    assert(Validator::validate_photograph_product("http://example.com/photo.jpg") == false);
    std::cout << "ValidatePhotographProduct Test Passed!" << std::endl;
}

void testValidateQuantityProduct() {
    assert(Validator::validate_quantity_product("10") == 10);
    assert(Validator::validate_quantity_product("2") == 2);
    assert(Validator::validate_quantity_product("abc") == -1);
    assert(Validator::validate_quantity_product("") == -1);
    std::cout << "ValidateQuantityProduct Test Passed!" << std::endl;
}


void callAllTests()
{
    testDefaultConstructor();
    testParameterizedConstructor();
    testSetQuantity();
    testSetPrice();
    testGetSize();
    testGetColor();
    testGetPrice();
    testGetQuantity();
    testGetPhotograph();
    testTokenize();
    testOperatorAssignment();
    testAddRepo();
    testDeleteRepo();
    testSoldOut();
    testAddDuplicateRepo();
    testAddService();
    testDeleteService();
    testUpdatePriceService();
    testUpdateQuantityService();
    testAddUserService();
    testGetFilteredRepository();
    testValidateColorProduct();
    testValidateSizeProduct();
    testValidatePriceProduct();
    testValidatePhotographProduct();
    testValidateQuantityProduct();
    std::cout << "All tests passed!" << std::endl;
}
