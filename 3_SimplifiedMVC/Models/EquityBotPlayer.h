#pragma once

#include "BasePlayer.h"


namespace Models {

    class EquityBotPlayer : public BasePlayer {
    public:
        EquityBotPlayer(unsigned int balance, const char* name);
        bool IsBot() override;
        Bet MakeDecision(const std::vector<Card>& board, const std::vector<unsigned int>& bets) override;
    };

}