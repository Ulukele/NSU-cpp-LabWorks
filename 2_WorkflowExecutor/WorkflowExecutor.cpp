#include "WorkflowExecutor.h"
#include "Factory/WorkersFactory.h"
#include "Factory/IWorker.h"

#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <regex>

#include "iostream"

using namespace Common;

WorkflowExecutor& WorkflowExecutor::Instance() {
    static WorkflowExecutor instance;
    return instance;
}

bool parse_str(
        std::string& str,
        std::map<std::string, std::vector<std::string>>& blocks,
        std::list<std::string>& order
        ) {
    std::regex base(R"(desc\s([^]*)\scsed\s([^]*))");
    std::smatch groups;
    if ( !std::regex_search(str, groups, base) ) {
        return false;
    }
    // definition of blocks
    const std::string blocs_s = groups[1].str();
    // definition of ordering
    const std::string order_s = groups[2].str();

    // parsing blocks and its args
    std::regex key_value(R"((\d*)\s*=\s*([^\n]*)\n?)");
    auto rows_begin = std::sregex_iterator(blocs_s.begin(), blocs_s.end(), key_value);
    auto rows_end = std::sregex_iterator();
    for (std::sregex_iterator i = rows_begin; i != rows_end; ++i) {
        std::smatch matched = *i;
        std::string key = matched[1];
        std::string args_s = matched[2];
        std::vector<std::string> args;

        // parse args
        std::stringstream s_stream(args_s);
        std::string value;
        while (std::getline(s_stream, value, ' ')) {
            args.push_back(value);
        }
        blocks[key] = args;
    }

    // parsing order
    std::regex node(R"( *(\d\d*)( *-> *)?)");
    auto nodes_begin = std::sregex_iterator(order_s.begin(), order_s.end(), node);
    auto nodes_end = std::sregex_iterator();
    for (std::sregex_iterator i = nodes_begin; i != nodes_end; ++i) {
        std::smatch matched = *i;
        order.push_back(matched[1]);
    }


    return true;
}

void WorkflowExecutor::Execute(const std::string &workflow_file) {
    std::ifstream input(workflow_file);
    std::stringstream buffer_;
    buffer_ << input.rdbuf();
    std::string workflow_raw = std::string( buffer_.str() );

    std::list<std::string> order;
    std::map<std::string, std::vector<std::string>> blocks;

    bool parsed = parse_str(workflow_raw, blocks, order);
    if ( !parsed ) {
        throw std::exception(); // TODO exception with text
    }

    for (const auto& node: order) {
        const auto iter = blocks.find(node);
        if ( iter == blocks.end()) {
            throw std::exception(); // TODO exception with 'item in order not defined'
        }
        IWorker worker = WorkersFactory::Instance().Create(*iter[0], )
    }

//    TODO: remove DEBUG cout's
//    for (const auto& node : order) {
//        std::cout << "(";
//        for (const auto& arg : blocks[node]) {
//            std::cout << arg << " ";
//        }
//        std::cout << ") -> ";
//    }
//    std::cout << std::endl;
}