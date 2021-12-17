#include "Board.h"

namespace Models {
    Board::Board() : BaseModel(), pool(0) {}

    unsigned int Board::GetPool() const { return pool; }
    const std::vector<Card>& Board::GetCards() const { return cards; }
    unsigned int Board::GetLastBet() const { return last_bet; }
    unsigned int Board::GetActivePlayer() const { return active_player_id; }

    void Board::AddCard(Card card) {
        cards.push_back(card);
        updater.Handle();
    }

    void Board::RaisePool(unsigned int value) {
        pool += value;
        updater.Handle();
    }

    void Board::Clear() {
        pool = 0;
        cards.resize(0);
        updater.Handle();
    }

    void Board::NullPool() {
        pool = 0;
        updater.Handle();
    }

    void Board::SetLastBet(unsigned int last) {
        last_bet = last;
        updater.Handle();
    }

    void Board::SetActivePlayer(unsigned int id) {
        active_player_id = id;
        updater.Handle();
    }

}