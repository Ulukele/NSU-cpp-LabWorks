#include "BaseModel.h"
#include <algorithm>

namespace Models {
    void BaseModel::AddUpdater(View::Updater* updater) {
        updaters.push_back(updater);
    }

    void BaseModel::RemoveUpdater(View::Updater* updater) {
        updaters.erase(std::remove(updaters.begin(), updaters.end(), updater), updaters.end());
    }

    void BaseModel::Update() {
        for (const auto& updater : updaters) {
            updater->Update();
        }
    }
}