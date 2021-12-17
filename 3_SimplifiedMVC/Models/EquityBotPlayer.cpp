#include "EquityBotPlayer.h"

#include <utility>
#include "set"

#include "../Common/Common.h"


namespace Models {
    EquityBotPlayer::EquityBotPlayer(unsigned int balance, unsigned int id, std::string name) : BasePlayer(balance, id, std::move(name)) {}

    bool EquityBotPlayer::IsBot() { return true; }

    Bet EquityBotPlayer::MakeDecision(
            const std::vector<Card> &board,
            unsigned int last_bet,
            unsigned int players_count
            ) {
        unsigned int max_bet = last_bet;
        unsigned int need = 0;
        if (max_bet > bet) {
            need = max_bet - bet;
        }

        if (balance < need) return Bet{FOLD, 0};

        double prob = Common::GetCombinationProbability(hand, board, players_count);
        prob *= 5.0 / (double) board.size();

        unsigned int target = 0;

        if (prob < 10 && need > 0) return Bet{FOLD, 0};
        if (prob >= 10 && prob < 20) {
            target = max_bet;
        }
        if (max_bet == 0) max_bet = (balance + bet) / 20;
        if (prob >= 20 && prob < 50) {
            if (bet == 0) target = (unsigned int) (max_bet * 1.2);
            else target = max_bet;
        }
        if (prob >= 50 && prob < 70) {
            if (bet == 0) target = (unsigned int) (max_bet * 1.3);
            else target = max_bet;
        }
        if (prob >= 70) {
            if (bet == 0) target = (unsigned int) (max_bet * 1.5);
            else target = max_bet;
        }
        unsigned int value = std::min(balance + bet, target);

        return Bet{RAISE, value};
    }
}