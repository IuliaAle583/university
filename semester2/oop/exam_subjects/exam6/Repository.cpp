#include "Repository.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Repository::loadIdeas()
{
    ifstream in(R"(D:\desktop2\teste_oop\exam6\exam6\ideas.txt)");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string title, description, status, creator, durStr;
        int duration;

        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, status, ',');
        getline(ss, creator, ',');
        getline(ss, durStr, ',');

        try {
            duration = stoi(durStr);
        }
        catch (...) {
            duration = 0;
        }

        if (!title.empty() && !creator.empty()) {
            ideas.emplace_back(title, description, status, creator, duration);
        }
    }
    in.close();
}

void Repository::loadResearchers()
{
    ifstream in(R"(D:\desktop2\teste_oop\exam6\exam6\reaserchers.txt)");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, position;

        getline(ss, name, ',');
        getline(ss, position, ',');

        if (!name.empty() && !position.empty()) {
            reaserchers.emplace_back(name, position);
        }
    }
    in.close();
}

void Repository::saveIdeas()
{
    ofstream out("ideasAccepted.txt");
    sort(ideas.begin(), ideas.end(), [](const Idea& a, const Idea& b) {
        return a.getDuration() < b.getDuration();
        });

    for (const auto& idea : ideas) {
        if (idea.getStatus() == "accepted") {
            out << idea.getTitle() << " ("
                << idea.getCreator() << "), "
                << idea.getDuration() << " months: "
                << idea.getDescription() << endl;
        }
    }
    out.close();
}

vector<Idea>& Repository::getIdeasSorted()
{
    std::sort(ideas.begin(), ideas.end(), [](const Idea& a, const Idea& b) {
        return a.getDuration() < b.getDuration();
        });
    return ideas;
}

bool Repository::acceptIdea(const string& title)
{
    for (auto& idea : ideas) {
        if (idea.getTitle() == title && idea.getStatus() == "proposed") {
            idea.setStatus("accepted");
            return true;
        }
    }
    return false;
}

vector<Idea> Repository::getAcceptedIdeasByResearcher(const string& name)
{
    vector<Idea> result;
    for (const auto& idea : ideas) {
        if (idea.getStatus() == "accepted" && idea.getCreator() == name) {
            result.push_back(idea);
        }
    }
    return result;
}

void Repository::updateIdeaDescription(const string& title, const string& newDescription)
{
    for (auto& idea : ideas) {
        if (idea.getTitle() == title) {
            idea.setDescription(newDescription);
            break;
        }
    }
}

void Repository::saveIdeaToFile(const string& title)
{
    for (const auto& idea : ideas) {
        if (idea.getTitle() == title && idea.getStatus() == "accepted") {
            ofstream out(title + ".txt");
            out << "Title: " << idea.getTitle() << "\n";
            out << "Creator: " << idea.getCreator() << "\n";
            out << "Duration: " << idea.getDuration() << "\n";
            out << "Description: " << idea.getDescription() << "\n";
            out.close();
            break;
        }
    }
}
