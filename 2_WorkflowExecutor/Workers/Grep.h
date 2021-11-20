#pragma once

#include <vector>
#include <string>
#include "../Factory/IWorker.h"

class Grep : public Common::IWorker {
public:
    Grep(std::vector< std::string >& args, std::string& data);
    ~Grep() override = default;
    std::string Execute() override;
    Common::WorkerType GetType() override;

private:
    std::string data;
    std::string key;
};
