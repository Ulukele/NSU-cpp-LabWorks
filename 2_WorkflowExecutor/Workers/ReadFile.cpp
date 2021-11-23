#include "ReadFile.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"
#include "../Exceptions/WorkerInitialization.h"

ReadFile::ReadFile (std::vector< std::string >& args, std::string& data_) {
    if ( args.empty() ) {
        throw WorkerInitialization("Missing arguments");
    }
    if ( args.size() > 1 ) {
        throw WorkerInitialization("Got more than 1 arguments");
    }
    input_file = args[0];
}

std::string ReadFile::Execute() {
    std::ifstream input(this->input_file);
    std::stringstream buffer_;
    buffer_ << input.rdbuf();
    auto result = std::string( buffer_.str() );
    return result;
}

Common::WorkerType ReadFile::GetType() {
    return Common::WorkerType::OUT;
}

// Register creator
static Common::WorkerCreator<ReadFile> maker("readfile");