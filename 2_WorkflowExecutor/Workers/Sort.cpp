#include "Sort.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../Factory/WorkersFactory.h"
#include "../Factory/WorkerCreator.h"
#include "../Exceptions/WorkerInitialization.h"

Sort::Sort (std::vector< std::string >& args, std::string& data_) {
    if ( !args.empty() ) {
        throw WorkerInitialization("Unexpected arguments");
    }
    data = data_;
}

std::string Sort::Execute() {
    std::istringstream in(data);
    std::vector<std::string> words;
    std::string word;
    while (in >> word) words.push_back(word);
    std::sort(words.begin(), words.end());
    std::string result;
    for (const auto &w : words) result += w + " ";
    return result;
}

Common::WorkerType Sort::GetType() {
    return Common::WorkerType::INOUT;
}

// Register creator
static Common::WorkerCreator<Sort> maker("sort");