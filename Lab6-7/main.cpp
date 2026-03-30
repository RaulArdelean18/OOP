#include "repo/repo.h"
#include "serv/service.h"
#include "ui/ui.h"

int main() {
    Repo repo;
    Service srv(repo);
    UI ui(srv);
    ui.run();
    return 0;
}