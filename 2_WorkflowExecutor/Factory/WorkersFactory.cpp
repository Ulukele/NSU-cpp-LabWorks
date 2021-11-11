#include <exception>
#include "WorkersFactory.h"

namespace Common {

    WorkersFactory& WorkersFactory::Instance() {
        static WorkersFactory instance;
        return instance;
    }

    void WorkersFactory::RegisterCreator(const std::string &worker_name, Common::IWorkerCreator* creator) {
        if (makers.find(worker_name) != makers.end()) {
            throw std::exception(); // TODO exception 'Multiple makers for given key!'
        }
        makers[worker_name] = creator;
    }
    IWorker* WorkersFactory::Create(const std::string& name, std::vector< std::string >& args) {
        auto iter_ = makers.find(name);
        if (iter_ == makers.end()) {
            throw std::exception(); // TODO exception 'Unrecognized worker type!'
        }
        IWorkerCreator* creator = iter_->second;
        return creator->Create(args);
    }
}