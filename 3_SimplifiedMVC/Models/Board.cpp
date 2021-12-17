#include "Board.h"

namespace Models {
    Board::Board() : BaseModel(), pool(0) {}

    unsigned int Board::GetPool() const { return pool; }
    const std::vector<Card>& Board::GetCards() const { return cards; }
    unsigned int Board::GetLastBet() const { return last_bet; }
    unsigned int Board::GetActivePlayer() const { return active_player_id; }

    void Board::AddCard(Card card) {
        cards.push_back(card);
        Update();
    }

    void Board::RaisePool(unsigned int value) {
        pool += value;
        Update();
    }

    void Board::Clear() {
        pool = 0;
        cards.resize(0);
        Update();
    }

    void Board::NullPool() {
        pool = 0;
        Update();
    }

    void Board::SetLastBet(unsigned int last) {
        last_bet = last;
        Update();
    }

    void Board::SetActivePlayer(unsigned int id) {
        active_player_id = id;
        Update();
    }

}