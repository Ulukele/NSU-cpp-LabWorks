#pragma once
#include "WorkersFactory.h"
#include "IWorkerCreator.h"

namespace Common {
    template <typename T>
    class WorkerCreator : public IWorkerCreator {
    public:
        WorkerCreator(const std::string& name) {
            WorkersFactory::Instance().RegisterCreator(name, this);
        }

        IWorker* Create(std::vector< std::string >& args, std::string& data) override {
            return new T(args, data);
        }
    };
}
