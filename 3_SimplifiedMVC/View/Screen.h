#pragma once

#include <vector>
#include <string>
#include "../Models/BasePlayer.h"
#include "../Models/Board.h"


namespace View {

    class Screen {
    public:
        static Screen &Instance();
        void Init(const std::vector<Models::BasePlayer*>& players_models, Models::Board* board_);
        void Update();

        Screen(const Screen& obj) = delete;
        Screen& operator=(const Screen& obj) = delete;
        ~Screen() = default;
    private:
        Screen() = default;
        std::vector<Models::BasePlayer*> players;
        Models::Board* board;
    };
}