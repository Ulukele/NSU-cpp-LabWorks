cmake_minimum_required(VERSION 3.19)
project(2_WorkflowExecutor)

set(CMAKE_CXX_STANDARD 14)

set(
        PROJECT_FILES_
        main.cpp
        Factory/WorkersFactory.cpp
        Factory/WorkersFactory.h
        Factory/IWorker.h
        Factory/IWorkerCreator.h
        Factory/WorkerCreator.h
        Workers/ReadFile.cpp
        Workers/ReadFile.h
        Workers/WriteFile.cpp
        Workers/WriteFile.h
        Workers/Dump.cpp
        Workers/Dump.h
        Workers/Sort.cpp
        Workers/Sort.h
        Workers/Replace.cpp
        Workers/Replace.h
        Workers/Grep.cpp
        Workers/Grep.h
        WorkflowExecutor.cpp
        WorkflowExecutor.h
        Exceptions/ConflictingBlockType.h
        Exceptions/UnknownBlock.h
        Exceptions/InvalidWorkflow.h
        Exceptions/RegisterWorker.h
        Exceptions/CreateWorker.h)

add_executable(2_WorkflowExecutor ${PROJECT_FILES_})