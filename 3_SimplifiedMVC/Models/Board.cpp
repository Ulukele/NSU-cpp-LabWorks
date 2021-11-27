#include "Board.h"

namespace Models {
    Board::Board() : pool(0) {}

    unsigned int Board::GetPool() const { return pool; }

    std::vector<Card>& Board::GetCards() { return cards; }

    void Board::AddCard(Card card) {
        cards.push_back(card);
    }

    void Board::RaisePool(unsigned int value) {
        pool += value;
    }

    void Board::Clear() {
        pool = 0;
        cards.resize(0);
    }

}