#include "WriteFile.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"
#include "../Exceptions/WorkerInitialization.h"

WriteFile::WriteFile(std::vector<std::string> &args, std::string& data_) {
    if ( args.empty() ) {
        throw WorkerInitialization("Missing arguments");
    }
    if ( args.size() > 1 ) {
        throw WorkerInitialization("Got more than 1 arguments");
    }
    output_file = args[0];
    data = data_;
}

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