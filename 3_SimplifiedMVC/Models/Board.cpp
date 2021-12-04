#include "Board.h"

namespace Models {
    Board::Board() : pool(0) {}

    unsigned int Board::GetPool() const { return pool; }

    const std::vector<Card>& Board::GetCards() const { return cards; }

    void Board::AddCard(Card card) {
        cards.push_back(card);
        updater.Handle();
    }

    void Board::RaisePool(unsigned int value) {
        pool += value;
        updater.Handle();
    }

    void Board::Clear() {
        pool = 0;
        cards.resize(0);
        updater.Handle();
    }

    void Board::ProcessWinners(const std::vector<BasePlayer*> &players,
                               const std::vector<std::vector<Card>> &combinations) {
        if (players.empty()) throw; // TODO

        unsigned int pool_part = pool / players.size();
        pool = 0;

        for (const auto& player : players) {
            player->RaiseBalance(pool_part);
        }

    }

}