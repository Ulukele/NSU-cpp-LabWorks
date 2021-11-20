#pragma once

#include <vector>
#include <string>
#include "../Factory/IWorker.h"

class Dump : public Common::IWorker {
public:
    Dump(std::vector< std::string >& args, std::string& data);
    ~Dump() override = default;
    std::string Execute() override;
    Common::WorkerType GetType() override;

private:
    std::string output_file;
    std::string data;
};
