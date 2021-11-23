#include "Dump.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"
#include "../Exceptions/WorkerInitialization.h"

Dump::Dump (std::vector< std::string >& args, std::string& data_) {
    if ( args.empty() ) {
        throw WorkerInitialization("Missing arguments");
    }
    if ( args.size() > 1 ) {
        throw WorkerInitialization("Got more than 1 arguments");
    }
    output_file = args[0];
    data = data_;
}

std::string Dump::Execute() {
    std::ofstream out(output_file);
    out << data;
    return data;
}

Common::WorkerType Dump::GetType() {
    return Common::WorkerType::INOUT;
}

// Register creator
static Common::WorkerCreator<Dump> maker("dump");