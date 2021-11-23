#pragma once

#include "BaseException.h"

class UnknownBlock : public BaseException
{
public:
    explicit UnknownBlock(): BaseException("Unknown block") {}
    explicit UnknownBlock(const std::string& message): BaseException(message) {}
};