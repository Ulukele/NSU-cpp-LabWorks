#include "ReadFile.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"

ReadFile::ReadFile (std::vector< std::string >& args) :
    input_file(args[0]),
    output(nullptr)
    {}

ReadFile::~ReadFile() {
    delete output;
}

std::string* ReadFile::Execute() {
    std::ifstream input(this->input_file);
    std::stringstream buffer_;
    buffer_ << input.rdbuf();
    output = new std::string( buffer_.str() );
    return output;
}

Common::WorkerType ReadFile::GetType() {
    return Common::WorkerType::OUT;
}

// Register creator
Common::WorkerCreator<ReadFile> maker("readfile");