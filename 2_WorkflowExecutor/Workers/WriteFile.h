#pragma once

#include <vector>
#include <string>
#include "../Factory/IWorker.h"

class WriteFile : public Common::IWorker {
public:
    WriteFile(std::vector< std::string >& args, std::string& data);
    ~WriteFile() override = default;
    std::string Execute() override;
    Common::WorkerType GetType() override;

private:
    std::string output_file;
    std::string data;
};