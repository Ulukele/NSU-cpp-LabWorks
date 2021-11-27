#pragma once

namespace Models {

    enum Suit {
        HEARTS,
        SPADES,
        DIAMONDS,
        CROSSES
    };

    struct Card {
        Suit suit;
        unsigned short value;
    };
}
