#pragma once
#include <string>
#include <vector>

class WorkflowExecutor {
public:
    void Execute(const std::string& workflow_file);

    WorkflowExecutor() = default;
    WorkflowExecutor(const WorkflowExecutor& obj) = default;
    WorkflowExecutor(WorkflowExecutor&& obj) noexcept = default;
    WorkflowExecutor& operator=(const WorkflowExecutor& obj) = default;
    WorkflowExecutor& operator=(WorkflowExecutor&& obj) noexcept = default;

    ~WorkflowExecutor() = default;
};
