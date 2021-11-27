#include "Screen.h"

namespace {
    void PrintCard(const Models::Card& card) {
        Models::Suit suit = card.suit;
        int suit_code = 0;
        if (suit == Models::Suit::CROSSES) suit_code = 5;
        if (suit == Models::Suit::DIAMONDS) suit_code = 4;
        if (suit == Models::Suit::HEARTS) suit_code = 3;
        if (suit == Models::Suit::SPADES) suit_code = 6;
        printf("%c", suit_code);

        if (card.value > 10) {
            if (card.value == 11) printf("J");
            if (card.value == 12) printf("D");
            if (card.value == 13) printf("K");
            if (card.value == 14) printf("A");
        }
        else {
            printf("%d", card.value);
        }
    }
}

namespace View {
    Screen& Screen::Instance() {
        static Screen instance;
        return instance;
    }

    void Screen::Init(const std::vector<Models::BasePlayer*>& players_models, Models::Board* board_) {
        players = players_models;
        board = board_;
        Update();
    }

    void Screen::Update() {
        for (const auto& player : players) {
            printf("%15s: %6u ", player->GetName(), player->GetBalance());
            if ( !player->IsBot() ) {
                auto hand = player->GetHand();
                PrintCard(hand.first);
                printf(" ");
                PrintCard(hand.second);
            }
            printf("\n");
        }
        printf("\n\nTable Cards: ");
        for (const auto& card : board->cards) {
            PrintCard(card);
            printf(" - ");
        }
    }
}