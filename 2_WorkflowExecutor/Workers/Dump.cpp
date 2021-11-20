#include "Dump.h"
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"

Dump::Dump (std::vector< std::string >& args, std::string& data) :
        output_file(args[0]),
        data(data)
{}

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