#include "service.h"
#include <utility>

Service::Service(Repository& repository, Repository& user_repository) :
    repository{ repository }, user_repository{ user_repository }, total_price{ 0 }
{
}

void Service::addService(std::string size, std::string color, int price, int quantity, std::string photograph) {
    this->repository.AddRepo(std::move(size), std::move(color), price, quantity, std::move(photograph));
}

const std::vector<TrenchCoat>& Service::GetRepository() {
    return this->repository.getArray();
}

std::vector<TrenchCoat> Service::GetUserRepository() {
    return this->user_repository.getArray();
}

int Service::GetSize() {
    return this->repository.GetSize();
}

void Service::deleteService(const std::string& size, const std::string& color, const std::string& photograph, int criteria) {
    if (criteria == 1) {
        this->repository.deleteRepo(size, color, photograph);
    }
    else if (criteria == 2) {
        this->repository.soldOut(size, color, photograph);
    }
}

void Service::updatePriceService(std::string size, std::string color, std::string photograph, int price) {
    this->repository.UpdatePriceRepo(std::move(size), std::move(color), std::move(photograph), price);
}

void Service::updateQuantityService(std::string size, std::string color, std::string photograph, int quantity) {
    this->repository.UpdateQuantityRepo(std::move(size), std::move(color), std::move(photograph), quantity);
}

int Service::addUserService(TrenchCoat coat, TrenchCoat cUser) {
    int index = this->user_repository.Check(cUser.GetSize(), cUser.GetColor(), cUser.GetPhotograph());
    if (index == -1) {
        this->user_repository.AddRepo(cUser.GetSize(), cUser.GetColor(), cUser.GetPrice(), cUser.GetQuantity(),
            coat.GetPhotograph());
        this->total_price = this->total_price + cUser.GetPrice();
    }
    else {
        int new_quantity = this->user_repository.getArray()[index].GetQuantity() + 1;
        this->user_repository.UpdateQuantityRepo(cUser.GetSize(), cUser.GetColor(), cUser.GetPhotograph(), new_quantity);
        this->total_price = this->total_price + cUser.GetPrice();
    }
    if (coat.GetQuantity() == 0) {
        this->repository.soldOut(coat.GetSize(), coat.GetColor(), coat.GetPhotograph());
        return 1;
    }
    return 0;
}

int Service::GetTotalPrice() const {
    return this->total_price;
}
std::vector<TrenchCoat> Service::GetFilteredRepository(std::string size) {
    if (size == "All sizes")
        return this->GetRepository();
    else {
        std::vector<TrenchCoat> elements(GetRepository().size());
        auto it = copy_if(GetRepository().begin(), GetRepository().end(), elements.begin(),
            [size](TrenchCoat coat) { return coat.GetSize() == size; });
        elements.resize(it - elements.begin());
        return elements;
    }
}


