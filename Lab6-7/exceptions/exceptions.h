//
// Created by Raul_A on 20/04/2026.
//

#ifndef LAB6_7_EXCEPTIONS_H
#define LAB6_7_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class DuplicatException : public std::runtime_error {
public:
    explicit DuplicatException(const std::string& msg) : std::runtime_error(msg) {}
};

class NotFoundException : public std::runtime_error {
public:
    explicit NotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& msg) : std::runtime_error(msg) {}
};

class CosException : public std::runtime_error {
public:
    explicit CosException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif //LAB6_7_EXCEPTIONS_H