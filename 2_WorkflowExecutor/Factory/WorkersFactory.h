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
        void RegisterCreator(const std::string &worker_name, IWorkerCreator *creator);
        IWorker* Create(const std::string& name, std::vector< std::string >& args);
    private:
        WorkersFactory() {};
        WorkersFactory(const WorkersFactory& obj);
        WorkersFactory& operator=(const WorkersFactory& obj);

        std::map<const std::string, IWorkerCreator*> makers;
    };
}
