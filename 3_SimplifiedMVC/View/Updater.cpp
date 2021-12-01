#include "Updater.h"
#include "Screen.h"

namespace View {
    void Updater::Handle() const {
        Screen::Instance().Update();
    }
}