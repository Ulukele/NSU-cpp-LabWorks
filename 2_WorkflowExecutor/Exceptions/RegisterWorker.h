#pragma once
#include <exception>
#include <utility>

class RegisterWorker : public std::exception
{
public:
    RegisterWorker() = default;

    explicit RegisterWorker(std::string  message): message(std::move(message)) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:

    std::string message = "Errors while register worker";
};