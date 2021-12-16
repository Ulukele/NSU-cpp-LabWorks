#include "Card.h"

namespace Models {
    bool operator==(Card first, Card second) {
        return first.value == second.value && first.suit == second.suit;
    }

    bool operator<(Card first, Card second) {
        if (first.value < second.value) return true;
        if (second.value < first.value) return false;
        return first.suit < second.suit;
    }
}

