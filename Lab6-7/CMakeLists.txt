cmake_minimum_required(VERSION 3.28)
project(Lab6_7)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab6_7
        main.cpp
        Domain/domain.cpp
        repo/repo.cpp
        serv/service.cpp
        ui/ui.cpp
)

add_executable(Lab6_7_tests
        tests/tests.cpp
        Domain/domain.cpp
        repo/repo.cpp
        serv/service.cpp
)