#pragma once

#include "Card.h"
#include <vector>
#include <string>
#include "BaseModel.h"


namespace Models {

    enum Action {
        FOLD,
        RAISE
    };

    struct Bet {
        Action action;
        unsigned int value;
    };

    class BasePlayer : public BaseModel {
    public:
        BasePlayer(unsigned int balance, unsigned int id, std::string name);

        std::string GetName() const;
        const std::pair<Card, Card>& GetHand() const;
        unsigned int GetBalance() const;
        unsigned int GetBet() const;
        bool GetPlaying() const;
        bool GetWinner() const;
        unsigned int GetCombinationLevel() const;
        const char* GetCombination() const;
        double GetProb() const;
        unsigned int GetId() const;

        bool MakeBet(unsigned int value);

        void RaiseBalance(unsigned int value);

        void SetHand(Card first, Card second);
        unsigned int SendBet();
        void SetPlaying(bool status);
        void SetWinner(bool status);
        void SetCombinationLevel(unsigned int level);
        void SetProb(double prob_);

        virtual bool IsBot() = 0;

        virtual Bet MakeDecision(
                const std::vector<Card> &board,
                unsigned int last_bet,
                unsigned int players_count
        ) = 0;

        void TriggerUpdate();

        virtual ~BasePlayer() = default;

    protected:
        unsigned int id;
        std::string name;
        unsigned int balance = 0;
        unsigned int bet = 0;
        double prob = 0.0;
        bool playing;
        std::pair<Card, Card> hand;

        bool winner;
        unsigned int combination_level{};
    };
}