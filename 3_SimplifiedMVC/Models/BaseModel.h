#pragma once
#include "../View/Updater.h"


namespace Models {
    class BaseModel {
    protected:
        View::Updater updater;
    };
}