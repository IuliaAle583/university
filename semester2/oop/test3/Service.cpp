#include "Service.h"
#include <algorithm>
#include <iterator>

vector<Domain> Service::getAll()
{
    vector<Domain> documents = repo.getAll();
    sort(documents.begin(), documents.end(), [](Domain& a, Domain& b) {return a.getContent().size() < b.getContent().size(); });
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
        
        if (a.getContent().find(smthing) != string::npos) {
            return true;
        }
        
        for (auto& x : a.getKeywords()) {
            if (x.find(smthing) != string::npos) {
                return true;
            }
        }
        return false;
        });
    return ans;
}

double Service::computeKeywordSimilarity(Domain& doc, const string& smthing)
{
    double totalSimilarity = 0.0;
    double length = 0;
    for (auto& keyword : doc.getKeywords())
        length += keyword.size();
    for (auto& keyword : doc.getKeywords()) {
        size_t foundPos = keyword.find(smthing);
        if (foundPos != string::npos) {
           // double similarity = static_cast<double>(smthing.length()) / keyword.length();
            double similarity = static_cast<double>(smthing.length()) / length;
            totalSimilarity += similarity;
        }
    }

    return totalSimilarity;
}






