#pragma once

namespace View {
    class Updater {
    public:
        explicit Updater() = default;

        virtual void Update() const = 0;

        Updater(const Updater &obj) = delete;
        Updater &operator=(const Updater &obj) = delete;
        ~Updater() = default;
    };
}
