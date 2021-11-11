#pragma once


namespace Common {
    enum WorkerType {
        IN,
        OUT,
        INOUT
    };

    class IWorker {
    public:
        virtual std::string* Execute() {};
        virtual WorkerType GetType() {};

        virtual ~IWorker() = default;
    };
}