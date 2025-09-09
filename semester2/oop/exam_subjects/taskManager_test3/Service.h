
#include "Repository.h"

class Service {
private:
    Repository& repo;

public:
    Service(Repository& r) : repo(r) {}

    vector<Task> getAllSorted() const;
    vector<Task> getByPriority(int p) const;
    int getTotalDurationByPriority(int p) const;
};

