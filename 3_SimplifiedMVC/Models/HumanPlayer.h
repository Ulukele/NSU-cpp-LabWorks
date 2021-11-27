#pragma once

#include "BasePlayer.h"


namespace Models {

    class HumanPlayer : public BasePlayer {
    public:
        HumanPlayer(unsigned int balance, const char* name);
        bool IsBot() override;
        Bet MakeDecision(const std::vector<Card>& board, const std::vector<unsigned int>& bets) override;
    };

}