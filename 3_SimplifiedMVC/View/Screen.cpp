#include "Screen.h"

namespace {
    void PrintCard(const Models::Card& card) {
        printf("[");
        if (card.value > 10) {
            if (card.value == 11) printf("J");
            if (card.value == 12) printf("D");
            if (card.value == 13) printf("K");
            if (card.value == 14) printf("A");
        }
        else {
            printf("%d", card.value);
        }
        Models::Suit suit = card.suit;
        if (suit == Models::Suit::CLUBS) printf("♣");
        if (suit == Models::Suit::DIAMONDS) printf("♦");
        if (suit == Models::Suit::HEARTS) printf("♥");
        if (suit == Models::Suit::SPADES) printf("♠");
        printf("]");
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
        printf("\033[H\033[J");
        printf("+---------------+---------+---------+---------+\n");
        printf("| Name:         | score:  | bet:    | cards:  |\n");
        printf("+---------------+---------+---------+---------+\n");
        for (const auto& player : players) {
            printf("|%15s| %6u$ | %6u$ |", player->GetName(), player->GetBalance(), player->GetBet());
            if ( !player->IsBot() ) {
                auto hand = player->GetHand();
                PrintCard(hand.first);
                printf(" ");
                PrintCard(hand.second);
                printf("|");
            }
            else {
                printf("         |");
            }
            printf("\n+---------------+---------+---------+---------+\n");
        }
        printf("\nTable Cards: ");
        for (const auto& card : board->GetCards()) {
            PrintCard(card);
            printf(" ");
        }
        printf("\n\n");
    }
}