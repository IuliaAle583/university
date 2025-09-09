
#include "Task.h"
#include <vector>
using namespace std;

class Repository {
private:
    vector<Task> tasks;

public:
    void loadFromFile(const string& filename);
    const vector<Task>& getAll() const;
};
