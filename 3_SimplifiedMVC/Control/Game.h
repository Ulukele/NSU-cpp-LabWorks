#pragma once

#include "../Models/BasePlayer.h"
#include "../Models/Board.h"
#include "../View/Screen.h"


namespace Control {

    enum State {
        FLOP, // 3 cards on table
        TURN, // 4 cards on table
        RIVER, // 5 cards on table
        END
    };

    class Game {
    public:
        Game(unsigned int num_bots, unsigned int num_playable, unsigned int start_balance);
        void Start();

        Game(const Game &obj) = delete;
        Game &operator=(const Game &obj) = delete;
        ~Game();

    private:
        View::Screen* screen;
        std::vector<Models::BasePlayer*> players;
        Models::Board* board;
        State state;
        std::vector<Models::Card> deck;

        void StartRound();
        void JudgeRound();
        void ProcessPlayersActions(unsigned int init_bet);
        bool ContinueRound();
        Models::Card PickOne();
        void InitPlayers();
        unsigned int GetPlayingCount();
        void RefreshPlayersProb();
    };
}

