#include "Common.h"
#include <random>
#include <algorithm>

namespace Common {

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
        if (cards.size() != 7) throw ; //TODO
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
        for (unsigned int cards_value : cards_values) {
            if (cards_value >= 2) pairs += 1;
            if (cards_value >= 3) thirds += 1;
            if (cards_value >= 4) comb = std::max(comb, 7);
        }
        if (pairs == 1) comb = std::max(comb, 1);
        if (pairs >= 2) comb = std::max(comb, 2);
        if (thirds > 0) comb = std::max(comb, 3);
        if (pairs > 0 && thirds > 0) comb = std::max(comb, 6);

        for (unsigned int cards_suit : cards_suits) {
            if (cards_suit >= 5) comb = std::max(comb, 5);
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

    const double MULTIPLIER = 15.0;
    const double MAX_COMB = MULTIPLIER * 10.0;
    double GetCombinationProbability(const std::vector<Models::Card>& cards) {
        if (cards.size() > 7) throw ; //TODO

        double prob = 0;

        int senior_card = 0;
        for (const auto& card: cards) {
            if (senior_card < card.value) senior_card = card.value;
        }
        prob = std::max(prob, senior_card * 1.0);

        unsigned int cards_values[MAX_VALUES]{0};
        unsigned int cards_suits[MAX_SUITS]{0};
        unsigned int cards_values_suits[MAX_VALUES][MAX_SUITS]{0};
        for (const auto& card: cards) {
            cards_values[card.value] += 1;
            cards_values_suits[card.value][card.suit] += 1;
            cards_suits[card.suit] += 1;
        }

        int singles = 0;
        int pairs = 0;
        int thirds = 0;
        for (unsigned int cards_value : cards_values) {
            if (cards_value == 1) singles += 1;
            if (cards_value == 2) pairs += 1;
            if (cards_value == 3) thirds += 1;
            if (cards_value >= 4) prob = std::max(prob, 7 * MULTIPLIER);
        }


        return prob / MAX_COMB;
    }
}