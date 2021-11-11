#pragma once

#include <vector>
#include <string>
#include "../Factory/IWorker.h"

class ReadFile : public Common::IWorker {
public:
    ReadFile(std::vector< std::string >& args);
    ~ReadFile() override;
    std::string* Execute() override;
    Common::WorkerType GetType() override;

private:
    std::string input_file;
    std::string* output;
};
