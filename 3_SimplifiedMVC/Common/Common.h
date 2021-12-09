#pragma once
#include <vector>
#include "../Models/Card.h"

namespace Common {

    const unsigned int MAX_VALUES = 15u;
    const unsigned int MIN_VALUE = 2u;
    const unsigned int MAX_SUITS = 4u;

    void FillDeck(std::vector<Models::Card>& deck);
    std::pair<int, int> GetCombinationLevel(const std::vector<Models::Card>& cards);
    double GetCombinationProbability(const std::vector<Models::Card>& cards);

}