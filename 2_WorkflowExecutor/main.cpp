#include <iostream>
#include "WorkflowExecutor.h"

int main() {
    try
    {
        WorkflowExecutor::Instance().Execute("../WorkflowsExamples/working.txt");
    }
    catch (std::exception &e)
    {
        std::cerr << "Error while executing workflow: " << e.what() << std::endl;
    }

    return 0;
}
