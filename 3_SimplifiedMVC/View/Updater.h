#pragma once

namespace View {
    class Updater {
    public:
        explicit Updater() = default;

        void Handle() const;

        Updater(const Updater &obj) = delete;
        Updater &operator=(const Updater &obj) = delete;
        ~Updater() = default;
    };
}
