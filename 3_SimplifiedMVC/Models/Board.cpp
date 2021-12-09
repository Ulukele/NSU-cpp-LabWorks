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

    void Board::NullPool() {
        pool = 0;
        updater.Handle();
    }

}