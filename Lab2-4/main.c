#include "repo/repo.h"
#include "service/service.h"
#include "ui/console.h"

int main() {

    Repo repo;
    init_repo(&repo);

    Service srv;
    init_service(&srv, &repo);

    Console ui;
    init_console(&ui, &srv);

    run(&ui);

    distruge_repo(&repo);
    return 0;
}
