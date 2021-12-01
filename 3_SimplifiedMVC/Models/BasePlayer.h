#pragma once

#include "Card.h"
#include <vector>
#include <string>
#include "BaseModel.h"


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

    class BasePlayer : public BaseModel {
    public:
        BasePlayer(unsigned int balance, const char* name);

        const char* GetName() const;
        std::pair<Card, Card> GetHand() const;
        unsigned int GetBalance() const;
        unsigned int GetBet() const;
        bool GetPlaying() const;

        bool MakeBet(unsigned int value);

        void RaiseBalance(unsigned int value);

        void SetHand(Card first, Card second);

        void SetPlaying(bool status);

        virtual bool IsBot() = 0;

        virtual Bet MakeDecision(const std::vector<Card>& board, const std::vector<unsigned int>& bets) = 0;

        virtual ~BasePlayer() = default;

    private:
        const char* name;
        unsigned int balance = 0;
        unsigned int bet = 0;
        bool playing;
        std::pair<Card, Card> hand;
    };
}