#include "Service.h"
#include <algorithm>
#include <iterator>

vector<Domain> Service::getAll()
{
    vector<Domain> documents = repo.getAll();
    sort(documents.begin(), documents.end(), [](Domain& a, Domain& b) {return a.getName() < b.getName(); });
    return documents;
}

vector<Domain> Service::search(string smthing) 
{
    vector<Domain> documents = repo.getAll();
    vector<Domain> ans;
    copy_if(documents.begin(), documents.end(), std::back_inserter(ans), [smthing](Domain& a) {
        if (a.getName().find(smthing) != string::npos) {
            return true;
        }
        for (auto x : a.getKeywords()) {
            if (x.find(smthing) != string::npos) {
                return true;
            }
        }
        return false;
        });
    return ans;
}


Domain Service::bestMatch(string smthing)
{
    std::vector<Domain> documents = repo.getAll();

    Domain ans = documents[documents.size() - 1];
    documents.pop_back();
    auto getScore = [smthing](Domain& a) {
        return a.getName().find(smthing) != std::string::npos
            ? smthing.size() / static_cast<double>(a.getName().size())
            : 0.0;
    };

    double bestScore = getScore(ans);

    for (auto x : documents) {
        double score = getScore(x);
        if (score > bestScore) {
            bestScore = score;
            ans = x;
        }
    }

    return ans;

}

