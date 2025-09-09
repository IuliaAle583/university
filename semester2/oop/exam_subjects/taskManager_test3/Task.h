
#include <string>
using namespace std;

class Task {
private:
    string description;
    int duration;
    int priority;

public:
    Task(const string& desc, int duration, int priority);
    string getDescription() const;
    int getDuration() const;
    int getPriority() const;
};
