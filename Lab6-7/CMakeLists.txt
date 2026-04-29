cmake_minimum_required(VERSION 3.28)
project(Lab6_7)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab6_7
        main.cpp
        Domain/domain.cpp
        repo/repo.cpp
        serv/service.cpp
        ui/ui.cpp
        validator/validator.cpp
        validator/validator.h
        exceptions/exceptions.h
        Undo/undo.h
)

add_executable(Lab6_7_tests
        tests/tests.cpp
        Domain/domain.cpp
        repo/repo.cpp
        serv/service.cpp
        validator/validator.cpp
        exceptions/exceptions.h
)

target_compile_options(Lab6_7 PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)
target_compile_options(Lab6_7_tests PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)