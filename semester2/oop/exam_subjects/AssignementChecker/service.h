#pragma once
#include "repository.h"
class Service {
private:
	Repository& repo;
public:
	//Service();
	Service(Repository& repo);
	~Service();
	bool addService(int id, const std::string& name, const std::string& solution);
	DynamicVector<Assignment> getAllService();
	DynamicVector<std::string> checkDishonestyService();
	int countWordsService(const std::string& text);
	int countCommonWordsService(const std::string& sol1, const std::string& sol2);
};
