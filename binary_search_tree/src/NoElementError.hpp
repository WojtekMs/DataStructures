#pragma once

#include <stdexcept>
#include <string>

class NoElementError: public std::exception {
    std::string msg_;
    public:
    template <typename ValueType>
    explicit NoElementError(ValueType&& val) {
        msg_ = "there is no element with value: " + std::to_string(std::forward<ValueType>(val));
    }
    const char* what() const noexcept override {
        return msg_.c_str();
    }
};
