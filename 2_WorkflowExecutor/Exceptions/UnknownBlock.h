#pragma once
#include <exception>
#include <utility>

class UnknownBlock : public std::exception
{
public:
    UnknownBlock() = default;

    explicit UnknownBlock(std::string  message): message(std::move(message)) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:

    std::string message = "Unknown block";
};