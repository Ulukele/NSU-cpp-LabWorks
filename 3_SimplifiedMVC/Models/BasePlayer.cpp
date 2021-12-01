#include "BasePlayer.h"

namespace Models {
    BasePlayer::BasePlayer(unsigned int balance, const char* name) :
        balance(balance),
        name(name)
        {};

    unsigned int BasePlayer::GetBalance() const { return balance; }
    unsigned int BasePlayer::GetBet() const { return bet; }
    const char* BasePlayer::GetName() const { return name; }
    std::pair<Card, Card> BasePlayer::GetHand() const { return hand; }
    bool BasePlayer::GetPlaying() const { return playing; }

    bool BasePlayer::MakeBet(unsigned int value) {
        if (balance >= value) {
            balance -= value;
            bet += value;
            updater.Handle();
            return true;
        }
        else {
            return false;
        }
    }

    void BasePlayer::RaiseBalance(unsigned int value) {
        balance += value;
        updater.Handle();
    }

    void BasePlayer::SetHand(Card first, Card second) {
        hand = std::make_pair(first, second);
        updater.Handle();
    }

    void BasePlayer::SetPlaying(bool status) {
        playing = status;
        updater.Handle();
    }

}
