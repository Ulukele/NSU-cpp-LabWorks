#pragma once

namespace Models {

    enum Suit {
        HEARTS,
        SPADES,
        DIAMONDS,
        CLUBS
    };

    struct Card {
        Suit suit;
        unsigned short value;
    };
}
