#pragma once

#include "BaseException.h"

class CreateWorker : public BaseException
{
public:
    explicit CreateWorker(): BaseException("Errors while creating worker") {}
    explicit CreateWorker(const std::string& message): BaseException(message) {}
};