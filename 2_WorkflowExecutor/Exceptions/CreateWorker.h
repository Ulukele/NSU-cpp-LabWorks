#pragma once
#include <exception>
#include <utility>

class CreateWorker : public std::exception
{
public:
    CreateWorker() = default;

    explicit CreateWorker(std::string  message): message(std::move(message)) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:

    std::string message = "Errors while creating worker";
};