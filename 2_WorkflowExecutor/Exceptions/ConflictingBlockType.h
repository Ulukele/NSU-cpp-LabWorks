#pragma once
#include <exception>
#include <utility>

class ConflictingBlockType : public std::exception
{
public:
    ConflictingBlockType() = default;

    explicit ConflictingBlockType(std::string  message): message(std::move(message)) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:

    std::string message = "Conflicting block type";
};