#include "HumanPlayer.h"

#include <utility>


namespace Models {
    HumanPlayer::HumanPlayer(unsigned int balance, unsigned int id, std::string name) : BasePlayer(balance, id, std::move(name)) {}
    bool HumanPlayer::IsBot() { return false; }
    Bet HumanPlayer::MakeDecision(
            const std::vector<Card> &board,
            unsigned int last_bet,
            unsigned int players_count
    ) {
        return Bet{FOLD, 0};
    }
}