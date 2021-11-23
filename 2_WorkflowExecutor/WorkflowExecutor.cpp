#include "WorkflowExecutor.h"
#include "Factory/WorkersFactory.h"
#include "Factory/IWorker.h"

#include "Exceptions/UnknownBlock.h"
#include "Exceptions/ConflictingBlockType.h"
#include "Exceptions/InvalidWorkflow.h"

#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <regex>
#include <memory>

using namespace Common;

WorkflowExecutor& WorkflowExecutor::Instance() {
    static WorkflowExecutor instance;
    return instance;
}

namespace {
    bool parse_str(
            std::string& str,
            std::map<std::string, std::string>& blocks_names,
            std::map<std::string, std::vector<std::string>>& blocks_args,
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


            std::stringstream s_stream(args_s);
            std::string value;

            // parse name
            std::getline(s_stream, value, ' ');
            blocks_names[key] = value;

            // parse args
            while (std::getline(s_stream, value, ' ')) {
                args.push_back(value);
            }
            blocks_args[key] = args;
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

    bool IsCompatible(WorkerType first, WorkerType second) {
        bool first_out = first == WorkerType::OUT || first == WorkerType::INOUT;
        bool second_in = second == WorkerType::IN || second == WorkerType::INOUT;

        if (first_out != second_in) return false;

        return true;
    }
}

void WorkflowExecutor::Execute(const std::string &workflow_file) {
    std::ifstream input(workflow_file);
    std::stringstream buffer_;
    buffer_ << input.rdbuf();
    std::string workflow_raw = std::string( buffer_.str() );

    std::list<std::string> order;
    std::map<std::string, std::string> blocks_names;
    std::map<std::string, std::vector<std::string>> blocks_args;

    bool parsed = parse_str(workflow_raw, blocks_names, blocks_args, order);
    if ( !parsed ) {
        throw InvalidWorkflow();
    }

    std::string input_data;
    auto previous_type = WorkerType::NONE;
    for (const auto& node: order) {
        const auto iter_args = blocks_args.find(node);
        const auto iter_names = blocks_names.find(node);
        if ( iter_args == blocks_args.end() || iter_names == blocks_names.end()) {
            throw UnknownBlock("Unknown block '" + node + "'");
        }
        std::unique_ptr<IWorker> worker(
                WorkersFactory::Instance().Create(iter_names->second, iter_args->second, input_data)
                );
        auto worker_type = worker->GetType();
        if ( !IsCompatible(previous_type, worker_type) ) {
            throw ConflictingBlockType();
        }
        previous_type = worker_type;

        input_data = worker->Execute();
    }


}