#include "HumanPlayer.h"


namespace Models {
    HumanPlayer::HumanPlayer(unsigned int balance, const char *name) : BasePlayer(balance, name) {}
    bool HumanPlayer::IsBot() { return false; }
    Bet HumanPlayer::MakeDecision(const std::vector<Card> &board, const std::vector<unsigned int> &bets) {
        return Bet{FOLD, 0};
    }
}