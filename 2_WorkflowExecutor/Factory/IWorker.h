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
        virtual std::string Execute() {return "";};
        virtual WorkerType GetType() {return WorkerType::NONE;};

        virtual ~IWorker() = default;
    };
}