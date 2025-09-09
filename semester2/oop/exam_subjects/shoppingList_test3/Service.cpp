
#include "Service.h"

std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool containsCaseInsensitive(const std::string& str, const std::string& substr) {
    std::string strLower = toLower(str);
    std::string substrLower = toLower(substr);
    return strLower.find(substrLower) != std::string::npos;
}

std::vector<Item> Service::getAllItems() {
    std::vector<Item> items = this->repository.getItems();
    std::sort(items.begin(), items.end());
    return items;
}

std::vector<Item> Service::getItemsByCategory(std::string category) {
    std::vector<Item> items = this->repository.getItems();
    std::vector<Item> filteredItems;
    for (auto item : items)
        if (item.getCategory() == category)
            filteredItems.push_back(item);
    std::sort(filteredItems.begin(), filteredItems.end(), Service::functionOfComparison);
    return filteredItems;
}

std::vector<Item> Service::getItemsThatContainString(std::string search) {
    std::vector<Item> items = this->repository.getItems();
    std::vector<Item> filteredItems;
    for (auto item : items)
        if (containsCaseInsensitive(item.getCategory(), search) ||
            containsCaseInsensitive(item.getName(), search))
            filteredItems.push_back(item);
    return filteredItems;
}