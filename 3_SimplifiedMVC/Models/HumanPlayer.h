#pragma once

#include "BasePlayer.h"


namespace Models {

    class HumanPlayer : public BasePlayer {
    public:
        HumanPlayer(unsigned int balance, unsigned int id, std::string name);
        bool IsBot() override;
        Bet MakeDecision(
                const std::vector<Card> &board,
                unsigned int last_bet,
                unsigned int players_count
        ) override;
    };

}