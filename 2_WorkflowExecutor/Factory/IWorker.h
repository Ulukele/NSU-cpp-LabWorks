#pragma once


namespace Common {
    enum WorkerType {
        IN,
        OUT,
        INOUT,
        NONE
    };

    class IWorker {
    public:
        virtual std::string Execute() = 0;
        virtual WorkerType GetType() = 0;

        virtual ~IWorker() = default;
    };
}