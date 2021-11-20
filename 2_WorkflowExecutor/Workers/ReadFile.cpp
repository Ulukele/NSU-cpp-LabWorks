#include "ReadFile.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"

ReadFile::ReadFile (std::vector< std::string >& args, std::string& data) :
    input_file(args[0])
    {}

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