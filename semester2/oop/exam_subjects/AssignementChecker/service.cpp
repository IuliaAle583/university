#include "service.h"

//Service::Service() { this->repo = Repository(); }

Service::Service(Repository& repo) : repo(repo)
{
}

Service::~Service()
{
	//nimic
}

bool Service::addService(int id, const std::string& name, const std::string& solution)
{
	DynamicVector<Assignment> teme = repo.getAll();
	for (int i = 0; i < teme.getSize(); i++) {
		if (teme[i].getId() == id) {
			return false;
		}
	}
	if (name.length() < 3 || solution.empty()) {
		return false;
	}
	repo.add(id, name, solution);
	return true;
}

DynamicVector<Assignment> Service::getAllService()
{
	return repo.getAll();
}

int Service::countWordsService(const std::string& text)
{
	return repo.countWords(text);
}

int Service::countCommonWordsService(const std::string& sol1, const std::string& sol2)
{
	return repo.countCommonWords(sol1,sol2);
}

DynamicVector<std::string> Service::checkDishonestyService()
{
	return repo.checkDishonesty();
}

