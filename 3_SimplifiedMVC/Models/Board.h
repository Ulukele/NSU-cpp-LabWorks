#pragma once

#include <vector>
#include "Card.h"


namespace Models {
    class Board {
    public:
        Board();

        std::vector<Card>& GetCards();
        unsigned int GetPool() const;
        void RaisePool(unsigned int value);
        void AddCard(Card card);
        void Clear();

        Board(const Board& obj) = delete;
        Board& operator=(const Board& obj) = delete;
        ~Board() = default;
    private:
        unsigned int pool;
        std::vector<Card> cards;
    };
}
