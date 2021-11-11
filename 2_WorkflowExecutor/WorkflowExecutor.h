#pragma once
#include <string>
#include <vector>

class WorkflowExecutor {
public:
    static WorkflowExecutor &Instance();
    void Execute(const std::string& workflow_file);

private:
    WorkflowExecutor() {};
    WorkflowExecutor(const WorkflowExecutor& obj);
    WorkflowExecutor& operator=(const WorkflowExecutor& obj);
};
