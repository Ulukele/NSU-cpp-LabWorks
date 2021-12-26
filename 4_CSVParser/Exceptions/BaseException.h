#pragma once
#include <string>
#include <exception>

namespace Exceptions {
    class BaseException : public std::exception {
    public:
        explicit BaseException() = default;

        explicit BaseException(const std::string &message) : message(message) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    protected:
        std::string message;
    };

}