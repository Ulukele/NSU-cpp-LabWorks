#include "Grep.h"
#include <regex>
#include <fstream>
#include <sstream>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"
#include "../Exceptions/WorkerInitialization.h"

Grep::Grep (std::vector< std::string >& args, std::string& data_) {
    if ( args.empty() ) {
        throw WorkerInitialization("Missing arguments");
    }
    if ( args.size() > 1 ) {
        throw WorkerInitialization("Got more than 1 arguments");
    }
    key = args[0];
    data = data_;
}

std::string Grep::Execute() {
    std::string regex_str = "[^\n]*(" + key + ")[^\n]*";
    std::regex row_exp(regex_str);

    std::regex_iterator<std::string::iterator> row (data.begin(), data.end(), row_exp);
    std::regex_iterator<std::string::iterator> end;

    std::string result;
    while (row != end)
    {
        result += row->str() + "\n";
        ++row;
    }
    return result;
}

Common::WorkerType Grep::GetType() {
    return Common::WorkerType::INOUT;
}

// Register creator
static Common::WorkerCreator<Grep> maker("grep");