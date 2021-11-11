#pragma once
#include <vector>
#include <string>
#include "IWorker.h"

namespace Common {

    class IWorkerCreator {
    public:
        virtual IWorker* Create(std::vector< std::string >& args) {};
        virtual ~IWorkerCreator() = default;
    };
}