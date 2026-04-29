#include "repo/repo.h"
#include "serv/service.h"
#include "ui/ui.h"
#include <iostream>

int main() {
    int opt;
    std::cout << "Repo (1=Vector, 2=Map): ";
    std::cin >> opt;

    if (opt == 1) {
        Repo repo;
        Service srv(repo);
        UI(srv).run();
    } else {
        RepoMap repo;
        Service srv(repo);
        UI(srv).run();
    }
}