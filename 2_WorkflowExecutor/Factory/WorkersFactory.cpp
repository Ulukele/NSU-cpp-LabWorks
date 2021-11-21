#include <exception>
#include "WorkersFactory.h"
#include "../Exceptions/RegisterWorker.h"
#include "../Exceptions/CreateWorker.h"

namespace Common {

    WorkersFactory& WorkersFactory::Instance() {
        static WorkersFactory instance;
        return instance;
    }

    void WorkersFactory::RegisterCreator(const std::string &worker_name, Common::IWorkerCreator* creator) {
        if (makers.find(worker_name) != makers.end()) {
            throw RegisterWorker("Multiple makers for given key: " + worker_name);
        }
        makers[worker_name] = creator;
    }
    IWorker* WorkersFactory::Create(const std::string& name, std::vector< std::string >& args, std::string data) {
        auto iter_ = makers.find(name);
        if (iter_ == makers.end()) {
            throw CreateWorker("Unrecognized worker type: " + name);
        }
        IWorkerCreator* creator = iter_->second;
        return creator->Create(args, data);
    }
}