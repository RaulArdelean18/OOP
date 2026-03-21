cmake_minimum_required(VERSION 3.28)
project(OOP C)

set(CMAKE_C_STANDARD 11)

add_executable(OOP
        main.c
        domain/car.c
        repo/repo.c
        service/service.c
        ui/console.c
        utils/vector.c
        validator/validator.c
)

add_executable(tests_runner
        test_main.c
        tests/test.c
        domain/car.c
        repo/repo.c
        service/service.c
        utils/vector.c
        validator/validator.c
)

target_compile_options(OOP PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)
target_compile_options(tests_runner PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)