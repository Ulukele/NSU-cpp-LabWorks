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
        WorkflowExecutor.cpp
        WorkflowExecutor.h
)

set(
        WORKFLOWS
        WorkflowsExamples/test1.txt
)

# Copying workflows to bin directory
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
    set(data_SHADOW ${WORKFLOWS})

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        FILE(COPY ${item} DESTINATION "${CMAKE_BINARY_DIR}/bin")
    endforeach()
endif()

add_executable(2_WorkflowExecutor ${PROJECT_FILES_})