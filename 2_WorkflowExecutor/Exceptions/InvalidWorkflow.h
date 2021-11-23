#pragma once

#include "BaseException.h"

class InvalidWorkflow : public BaseException
{
public:
    explicit InvalidWorkflow(): BaseException("Errors while register worker") {}
};