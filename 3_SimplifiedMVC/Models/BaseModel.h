#pragma once
#include <vector>
#include "../View/Updater.h"


namespace Models {
    class BaseModel {
    public:
        void AddUpdater(View::Updater* updater);
        void RemoveUpdater(View::Updater* updater);
        void Update();

    protected:
        std::vector<View::Updater*> updaters;
    };
}