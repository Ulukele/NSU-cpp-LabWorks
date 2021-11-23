#pragma once

#include <vector>
#include <string>
#include "../Factory/IWorker.h"

class Replace : public Common::IWorker {
public:
    Replace(std::vector< std::string >& args, std::string& data_);
    ~Replace() override = default;
    std::string Execute() override;
    Common::WorkerType GetType() override;

private:
    std::string data;
    std::string for_replace;
    std::string value;
};
