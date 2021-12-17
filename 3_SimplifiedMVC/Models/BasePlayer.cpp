#include "BasePlayer.h"

#include <utility>
#include "Combinations.h"
#include "../Common/Common.h"
#include "../Common/Exception.h"

namespace Models {
    BasePlayer::BasePlayer(unsigned int balance, unsigned int id, std::string name) :
        id(id),
        balance(balance),
        name(std::move(name)),
        playing(false),
        winner(false),
        BaseModel()
        {};

    unsigned int BasePlayer::GetBalance() const { return balance; }
    unsigned int BasePlayer::GetBet() const { return bet; }
    std::string BasePlayer::GetName() const { return name; }
    const std::pair<Card, Card>& BasePlayer::GetHand() const { return hand; }
    bool BasePlayer::GetPlaying() const { return playing; }
    bool BasePlayer::GetWinner() const { return winner; }
    unsigned int BasePlayer::GetCombinationLevel() const { return combination_level; }
    const char * BasePlayer::GetCombination() const { return COMBINATIONS[combination_level]; }
    double BasePlayer::GetProb() const { return prob; }
    unsigned int BasePlayer::GetId() const { return id; }

    bool BasePlayer::MakeBet(unsigned int value) {
        if (value < bet) return false;
        value -= bet;
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

    unsigned int BasePlayer::SendBet() {
        unsigned int value = bet;
        bet = 0;
        return value;
    }

    void BasePlayer::SetPlaying(bool status) {
        playing = status;
        updater.Handle();
    }

    void BasePlayer::SetWinner(bool status) {
        winner = status;
        updater.Handle();
    }

    void BasePlayer::SetCombinationLevel(unsigned int level) {
        if (combination_level >= COMBINATIONS_COUNT) throw Exception::Exception("Invalid combination level");
        combination_level = level;
    }

    void BasePlayer::SetProb(double prob_) {
        prob = prob_;
        updater.Handle();
    }

    void BasePlayer::TriggerUpdate() {
        updater.Handle();
    };

}
