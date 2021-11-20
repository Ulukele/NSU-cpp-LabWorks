#include "WriteFile.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"

WriteFile::WriteFile(std::vector<std::string> &args, std::string& data):
    output_file(args[0]),
    data(data)
    {}

std::string WriteFile::Execute() {
    std::ofstream out(output_file);
    out << data;
    return "";
}

Common::WorkerType WriteFile::GetType() {
    return Common::WorkerType::IN;
}

// Register creator
Common::WorkerCreator<WriteFile> maker("writefile");