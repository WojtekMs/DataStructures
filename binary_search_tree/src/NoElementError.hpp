#pragma once

#include <stdexcept>
#include <string>

class NoElementError: public std::exception {
    std::string errorMsg_{};
    public:
    explicit NoElementError(const std::string& str) : errorMsg_(str) {}
    const char* what() const noexcept override {
        return errorMsg_.c_str();
    }
};
