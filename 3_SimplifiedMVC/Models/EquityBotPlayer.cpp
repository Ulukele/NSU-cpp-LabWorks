#include "EquityBotPlayer.h"


namespace Models {
    EquityBotPlayer::EquityBotPlayer(unsigned int balance, const char *name) : BasePlayer(balance, name) {}
    bool EquityBotPlayer::IsBot() { return true; }
    Bet EquityBotPlayer::MakeDecision(const std::vector<Card> &board, const std::vector<unsigned int> &bets) {
        return Bet{FOLD, 0};
    }
}