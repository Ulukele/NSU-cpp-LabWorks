#pragma once

#include <vector>
#include "Card.h"
#include "BaseModel.h"
#include "BasePlayer.h"


namespace Models {
    class Board : public BaseModel {
    public:
        Board();

        const std::vector<Card>& GetCards() const;
        unsigned int GetPool() const;
        unsigned int GetLastBet() const;
        void RaisePool(unsigned int value);
        void NullPool();
        void AddCard(Card card);
        void Clear();
        void SetLastBet(unsigned int last);

        Board(const Board& obj) = delete;
        Board& operator=(const Board& obj) = delete;
        ~Board() = default;
    private:

        unsigned int pool;
        unsigned int last_bet;
        std::vector<Card> cards;
    };
}

