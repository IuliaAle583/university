#pragma once
#include "Domain.h"
#include <vector>
#include <algorithm>

class Repository
{
private:
	vector<Reasercher> reaserchers;
	vector<Idea> ideas;
public:
	void loadIdeas();
	void loadResearchers();
	Repository() {
		loadIdeas();
		loadResearchers();
	}
	void saveIdeas();	//will contiant the title, creator in brackets, duration, description and will be sorted by duration
	vector<Reasercher>& getReaserchers() { return reaserchers; }
	vector<Idea>& getIdeas()
	{
		return ideas; // fără sort!
	}

	vector<Idea>& getIdeasSorted();	//sort by duration
	void addIdea(Idea& idea) {
		ideas.emplace_back(idea);
	}
	bool acceptIdea(const string& title);
	vector<Idea> getAcceptedIdeasByResearcher(const string& name);
	void updateIdeaDescription(const string& title, const string& newDescription);
	void saveIdeaToFile(const string& title);
};

