#include "UI.h"
#include "service.h"
#include "tests.h"

int main() {
    Repository repo;
    Service service(repo);
    UI ui(service);
    callAllTests();
    ui.run();

    return 0;
}
