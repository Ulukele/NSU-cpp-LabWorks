#include "Replace.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"
#include "../Exceptions/WorkerInitialization.h"

Replace::Replace (std::vector< std::string >& args, std::string& data_) {
    if ( args.size() < 2 ) {
        throw WorkerInitialization("Missing arguments");
    }
    if ( args.size() > 2 ) {
        throw WorkerInitialization("Got more than 2 arguments");
    }
    for_replace = args[0];
    value = args[1];
    data = data_;
}

std::string Replace::Execute() {
    size_t index = 0;

    while ((index = data.find(for_replace, index)) != std::string::npos) {
        data.replace(index, for_replace.length(), value);
        index += value.length();
    }
    return data;
}

Common::WorkerType Replace::GetType() {
    return Common::WorkerType::INOUT;
}

// Register creator
static Common::WorkerCreator<Replace> maker("replace");