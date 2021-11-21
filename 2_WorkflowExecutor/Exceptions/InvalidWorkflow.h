#pragma once
#include <exception>
#include <utility>

class InvalidWorkflow : public std::exception
{
public:
    InvalidWorkflow() = default;

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:

    std::string message = "Workflow is invalid";
};