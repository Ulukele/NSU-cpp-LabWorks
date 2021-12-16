#include "Common.h"
#include "Montecarlo.h"
#include <random>
#include <algorithm>
#include <string>
#include "Exception.h"

namespace {
    std::string CardToString(Models::Card card) {
        std::string str;
        if (card.value > 10) {
            if (card.value == 11) str = "J";
            if (card.value == 12) str = "D";
            if (card.value == 13) str = "K";
            if (card.value == 14) str = "A";
        }
        else {
            str = std::to_string(card.value);
        }
        Models::Suit suit = card.suit;
        if (suit == Models::Suit::CLUBS) str += "C";
        if (suit == Models::Suit::DIAMONDS) str += "D";
        if (suit == Models::Suit::HEARTS) str += "H";
        if (suit == Models::Suit::SPADES) str += "S";

        return str;
    }
}

namespace Common {

    void FillOrdered(std::vector<Models::Card>& set) {
        set.clear();
        for (unsigned short i = Common::MIN_VALUE; i < Common::MAX_VALUES; ++i ) {
            set.push_back(Models::Card{Models::Suit::SPADES, i});
            set.push_back(Models::Card{Models::Suit::HEARTS, i});
            set.push_back(Models::Card{Models::Suit::DIAMONDS, i});
            set.push_back(Models::Card{Models::Suit::CLUBS, i});
        }
    }

    void FillDeck(std::vector<Models::Card>& deck) {
        deck.resize(0);
        for (unsigned short i = Common::MIN_VALUE; i < Common::MAX_VALUES; ++i ) {
            deck.push_back(Models::Card{Models::Suit::SPADES, i});
            deck.push_back(Models::Card{Models::Suit::HEARTS, i});
            deck.push_back(Models::Card{Models::Suit::DIAMONDS, i});
            deck.push_back(Models::Card{Models::Suit::CLUBS, i});
        }

        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(deck.begin(), deck.end(), generator);
    }

    std::pair<int, int> GetCombinationLevel(const std::vector<Models::Card>& cards) {
        if (cards.size() != 7) throw Exception::Exception("Invalid number of cards in combination, should be 7");
        int comb = 0;
        int senior_card = 0;
        for (const auto& card: cards) {
            if (senior_card < card.value) senior_card = card.value;
        }

        unsigned int cards_values[MAX_VALUES]{0};
        unsigned int cards_suits[MAX_SUITS]{0};
        unsigned int cards_values_suits[MAX_VALUES][MAX_SUITS]{0};
        for (const auto& card: cards) {
            cards_values[card.value] += 1;
            cards_values_suits[card.value][card.suit] += 1;
            cards_suits[card.suit] += 1;
        }

        int pairs = 0;
        int thirds = 0;
        for (unsigned int cards_value_count : cards_values) {
            if (cards_value_count >= 2) pairs += 1;
            if (cards_value_count >= 3) thirds += 1;
            if (cards_value_count >= 4) comb = std::max(comb, 7);
        }
        if (pairs == 1) comb = std::max(comb, 1);
        if (pairs >= 2) comb = std::max(comb, 2);
        if (thirds > 0) comb = std::max(comb, 3);
        if (pairs > 1 && thirds > 0) comb = std::max(comb, 6);

        for (unsigned int cards_suit_count : cards_suits) {
            if (cards_suit_count >= 5) comb = std::max(comb, 5);
        }

        for (const auto& card: cards) {
            int l = card.value;
            int s = card.suit;
            if (l + 5 > MAX_VALUES) continue;

            bool valid = true;
            bool one_suit = true;
            for (int r = l + 1; r < l + 5; ++r) {
                if (cards_values[r] == 0) {
                    valid = false;
                }
                if (cards_values_suits[r][s] == 0) {
                    one_suit = false;
                }
            }
            if (valid) {
                comb = std::max(comb, 4);
                if (one_suit) {
                    comb = std::max(comb, 8);
                    if (l == MAX_VALUES - 5) comb = std::max(comb, 9);
                }
            }
        }

        return std::make_pair(comb, senior_card);
    }

    double GetCombinationProbability(
            const std::pair<Models::Card, Models::Card>& hand,
            const std::vector<Models::Card>& board_cards,
            int number_of_players
            ) {

            std::set<std::string> hand_s;
            hand_s.insert( CardToString(hand.first) );
            hand_s.insert( CardToString(hand.first) );

            std::set<std::string> board_s;
            for (const auto& card : board_cards) {
                board_s.insert(CardToString(card) );
            }

            return Montecarlo::montecarlo(hand_s, board_s, number_of_players, 1000);
    }
}