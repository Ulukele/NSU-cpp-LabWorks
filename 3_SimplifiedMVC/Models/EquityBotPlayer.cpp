#include "EquityBotPlayer.h"


namespace Models {
    EquityBotPlayer::EquityBotPlayer(unsigned int balance, const char *name) : BasePlayer(balance, name) {}

    bool EquityBotPlayer::IsBot() { return true; }

    Bet EquityBotPlayer::MakeDecision(const std::vector<Card> &board, const std::vector<unsigned int> &bets) {
        unsigned int max_bet = 0;
        for (const auto& bet: bets) max_bet = std::max(max_bet, bet);



        return Bet{FOLD, 0};
    }
}