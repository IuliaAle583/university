#include "repository.h"
#include <sstream>
#include <set>
#include <cstring>
#include <iostream>

Repository::Repository()
{
	this->assigns = DynamicVector<Assignment>();

}

Repository::Repository(std::string fileName) :fileName(fileName)
{	
	// this->fileName = fileName; e same shit cu :fileName(fileName)
	readFromFile();
}

Repository::~Repository()
{

}

void Repository::readFromFile()
{
	std::ifstream fin(fileName);
	assigns.clear();
	int id;
	std::string name, solution, line;

	while (getline(fin,line)) {	//getline(fin, line) citeste o linie intreaga din fisier
		std::istringstream iss(line);	//iss este un flux de date care permite sa extragem informatiile bucata cu bucata din line
		iss >> id;
		iss.ignore();	//ignora caracterul separator
		getline(iss, name, ',');	//Citeste numele pana la separatorul ,
		getline(iss, solution);		//citeste restul
		assigns.append(Assignment{id, name, solution });
	}
	fin.close();
}

void Repository::writeToFile()
{
	std::ofstream fout(fileName);
	for (int i = 0; i < assigns.getSize(); i++) {
		fout << assigns[i].getId() << " "
			<< assigns[i].getName() << ","
			<< assigns[i].getSolution() << "\n";	//scrie in acelasi format ca in cel care citeste
	}
	fout.close();
}

void Repository::add(int id, const std::string& name, const std::string& solution)
{
	assigns.append(Assignment{ id, name, solution });
	writeToFile();		// sa nu uit sa apelez asta aici
}

DynamicVector<Assignment> Repository::getAll()
{
	return assigns;
}

int Repository::countWords(const std::string& text)
{
	std::istringstream iss(text);
	//Creeaz? un flux (iss) care cite?te con?inutul ?irului text ca ?i cum ar fi un flux de intrare
	//Un std::istream_iterator<std::string> este un iterator special care cite?te cuvinte dintr-un flux.
	//la cel fara parametrii: Acest constructor creeaz? un iterator de sfâr?it, care marcheaz? faptul c? nu mai sunt cuvinte de citit
	//std::distance m?soar? num?rul de elemente dintre cei doi iteratori, adic? num?rul de cuvinte din text
	//deci va returna nr de cuvinte
	return std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
	/*
	pot face si asa
	std::istringstream iss(text);
    std::string word;
    int count = 0;

    for (; iss >> word; count++); // Ruleaz? cât timp exist? cuvinte de citit
    
    return count;
	*/
}


int Repository::countCommonWords(const std::string& sol1, const std::string& sol2)
{
	std::set<std::string> words1, words2;
	std::istringstream iss1(sol1), iss2(sol2);
	std::string word;

	while (iss1 >> word) words1.insert(word);
	while (iss2 >> word) words2.insert(word);

	//int count = 0;
	//for (const auto& w : words1) {
	//	if (words2.count(w)) count++;
	//}
	int count = 0;
	for (const std::string& word : words1) {  
		if (words2.find(word) != words2.end()) {  //returneaza iteratori pe pozitia unde l-o gasit in set
			//daca nu l-a gasit va fi la end, de aia trebuie sa verific ca nu am ajuns acolo cumva
			count++;  
		}
	}
	return count;
}

/*
int Repository::countCommonWords(const std::string& sol1, const std::string& sol2) {
	//aparent nu se poate folosi strtok pe 2 siruri de-o data
	char* sol1_copy = new char[sol1.length() + 1];  
	char* sol2_copy = new char[sol2.length() + 1];
	std::strcpy(sol1_copy, sol1.c_str());
	std::strcpy(sol2_copy, sol2.c_str());
	char* saveptr1;
	char* saveptr2;

	//char* token1 = strtok_r(sol1_copy, " ",&saveptr1);  
	char* token2 = strtok(sol2_copy, " ");

	int count = 0;
	
	
	while (token1 != NULL) {
		//token2 = strtok(sol2_copy, " ,.!");
		while (token2 != NULL) {
			std::cout << "Comparing: " << token1 << " with " << token2 << std::endl;
			if (std::strcmp(token1, token2) == 0) {  
				std::cout << "Match found: " << token1 << std::endl;
				count++;
				//break;  
			}
			token2 = strtok(NULL, " ,.!");  
		}
		token1 = strtok(NULL, " ,.!");  
		token2 = strtok(sol2_copy, " ,.!");  
	}
	while (token1 != NULL) {
		token2 = strtok(sol2_copy, " ");
		while (token2 != NULL) {
			if (strcmp(token1, token2) == 0) {
				count++;
			}
			token2 = strtok(NULL, " ");
		}
		token1 = strtok(NULL, " ");
	}

	std::cout <<"common words"<< count << std::endl;
	return count;
}*/


DynamicVector<std::string> Repository::checkDishonesty()
{
	DynamicVector<std::string> results;
	for (int i = 0; i < assigns.getSize(); i++) {
		for (int j = 0; j < assigns.getSize(); j++) {
			if (i != j) {
				int commonWords = countCommonWords(assigns[i].getSolution(), assigns[j].getSolution());
				double per = (double)commonWords / countWords(assigns[j].getSolution()) * 100;
				//daca puneam int acolo dadea 0 pt ca sunt prea mici nr
				if (per >= 20) {
					std::ostringstream oss;
					oss << assigns[i].getName() << " - " << assigns[j].getName()
						<< " (" << per << "% of " << assigns[j].getName() << "'s solution)";

					results.append(oss.str());
			}
			}
		}
	}
	return results;
}
/*
DynamicVector<std::string> Repository::checkDishonesty() {
	DynamicVector<std::string> results;
	for (int i = 0; i < assigns.getSize(); i++) {
		for (int j = i+1; j < assigns.getSize(); j++) {
			
			int commonWords = countCommonWords(assigns[i].getSolution(), assigns[j].getSolution());
			double per = (double)commonWords / countWords(assigns[j].getSolution()) * 100;
			std::cout <<"percentage" << per << std::endl;
			if (per >= 20) {
				std::ostringstream oss;
				oss << assigns[i].getName() << " - " << assigns[j].getName()
				<< " (" << per << "% of " << assigns[j].getName() << "'s solution)";
				results.append(oss.str());
				
			}
		}
	}
	return results;
}*/



