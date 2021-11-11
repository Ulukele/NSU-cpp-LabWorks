#include <iostream>
#include <string>
#include "WorkflowExecutor.h"

int main() {
    WorkflowExecutor::Instance().Execute("../WorkflowsExamples/test1.txt");
    return 0;
}
