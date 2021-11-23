#pragma once

#include "BaseException.h"

class RegisterWorker : public BaseException
{
public:
    explicit RegisterWorker(): BaseException("Errors while register worker") {}
    explicit RegisterWorker(const std::string& message): BaseException(message) {}
};