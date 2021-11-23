#pragma once
#include <map>
#include <string>
#include <vector>
#include "IWorker.h"
#include "IWorkerCreator.h"

namespace Common {
    class WorkersFactory {
    public:
        static WorkersFactory &Instance();

        WorkersFactory(const WorkersFactory& obj) = delete;
        WorkersFactory& operator=(const WorkersFactory& obj) = delete;

        void RegisterCreator(const std::string &worker_name, IWorkerCreator *creator);
        IWorker* Create(const std::string& name, std::vector< std::string >& args, std::string data);
    private:
        WorkersFactory() = default;
        std::map<const std::string, IWorkerCreator*> makers;
    };
}
