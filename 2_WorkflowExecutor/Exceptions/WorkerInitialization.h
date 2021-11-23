#pragma once

#include "BaseException.h"

class WorkerInitialization : public BaseException
{
public:
    explicit WorkerInitialization(): BaseException("Problems while initializing worker") {}
    explicit WorkerInitialization(const std::string& message): BaseException(message) {}
};