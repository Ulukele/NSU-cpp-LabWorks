#include "BasePlayer.h"
#include "Combinations.h"

namespace Models {
    BasePlayer::BasePlayer(unsigned int balance, const char* name) :
        balance(balance),
        name(name),
        playing(false),
        winner(false),
        BaseModel()
        {};

    unsigned int BasePlayer::GetBalance() const { return balance; }
    unsigned int BasePlayer::GetBet() const { return bet; }
    const char* BasePlayer::GetName() const { return name; }
    const std::pair<Card, Card>& BasePlayer::GetHand() const { return hand; }
    bool BasePlayer::GetPlaying() const { return playing; }
    bool BasePlayer::GetWinner() const { return winner; }
    unsigned int BasePlayer::GetCombinationLevel() const { return combination_level; }
    const char * BasePlayer::GetCombination() const { return COMBINATIONS[combination_level]; }

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
        if (combination_level >= COMBINATIONS_COUNT) throw; // TODO
        combination_level = level;
    }

}
