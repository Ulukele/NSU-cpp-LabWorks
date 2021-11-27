#pragma once

#include "Card.h"
#include <vector>
#include <string>


namespace Models {

    enum Action {
        FOLD,
        CHECK,
        RAISE,
    };

    struct Bet {
        Action action;
        unsigned int value;
    };

    class BasePlayer {
    public:
        BasePlayer(unsigned int balance, const char* name);

        const char* GetName() const;
        std::pair<Card, Card> GetHand() const;
        unsigned int GetBalance() const;

        bool MakeBet(unsigned int value);

        void RaiseBalance(unsigned int value);

        const std::pair<Card, Card>& GetHand();

        void SetHand(Card first, Card second);

        virtual bool IsBot() = 0;

        virtual Bet MakeDecision(const std::vector<Card>& board, const std::vector<unsigned int>& bets) = 0;

        virtual ~BasePlayer() = default;

    private:
        const char* name;
        unsigned int balance = 0;
        std::pair<Card, Card> hand;
    };
}