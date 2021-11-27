#pragma once

#include "../Models/BasePlayer.h"
#include "../Models/HumanPlayer.h"
#include "../Models/Board.h"


namespace Control {
    class Game {
    public:
        Game(unsigned int num_players, unsigned int start_balance);
        void Start();
        void Round();


        Game(const Game &obj) = delete;
        Game &operator=(const Game &obj) = delete;

    private:
        ~Game();
        std::vector<Models::BasePlayer*> players;
        Models::Board* board;
    };
}

