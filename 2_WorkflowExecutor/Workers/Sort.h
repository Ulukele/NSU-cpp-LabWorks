#pragma once

#include <vector>
#include <string>
#include "../Factory/IWorker.h"

class Sort : public Common::IWorker {
public:
    Sort(std::vector< std::string >& args, std::string& data);
    ~Sort() override = default;
    std::string Execute() override;
    Common::WorkerType GetType() override;

private:
    std::string data;
};
