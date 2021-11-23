#pragma once

#include "BaseException.h"

class ConflictingBlockType : public BaseException
{
public:
    explicit ConflictingBlockType(): BaseException("Conflicting block type") {}
    explicit ConflictingBlockType(const std::string& message): BaseException(message) {}
};