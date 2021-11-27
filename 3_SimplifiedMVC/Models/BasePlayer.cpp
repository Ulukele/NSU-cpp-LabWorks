#include "BasePlayer.h"

namespace Models {
    BasePlayer::BasePlayer(unsigned int balance, const char* name) :
        balance(balance),
        name(name)
        {};

    unsigned int BasePlayer::GetBalance() const { return balance; }
    const char* BasePlayer::GetName() const { return name; }
    std::pair<Card, Card> BasePlayer::GetHand() const { return hand; }

    bool BasePlayer::MakeBet(unsigned int value) {
        if (balance >= value) {
            balance -= value;
            return true;
        }
        else {
            return false;
        }
    }

    void BasePlayer::RaiseBalance(unsigned int value) {
        balance += value;
    }

    void BasePlayer::SetHand(Card first, Card second) {
        hand = std::make_pair(first, second);
    }

    const std::pair<Card, Card>& BasePlayer::GetHand() {
        return hand;
    }
}
