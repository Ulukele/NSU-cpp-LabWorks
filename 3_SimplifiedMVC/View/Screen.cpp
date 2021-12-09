#include "Screen.h"

namespace {
    void PrintCard(const Models::Card& card, bool sep=false) {
        printf("[");
        if (card.value > 10) {
            if (card.value == 11) printf(" J");
            if (card.value == 12) printf(" D");
            if (card.value == 13) printf(" K");
            if (card.value == 14) printf(" A");
        }
        else {
            printf("%2d", card.value);
        }
        Models::Suit suit = card.suit;
        if (suit == Models::Suit::CLUBS) printf("♣");
        if (suit == Models::Suit::DIAMONDS) printf("♦");
        if (suit == Models::Suit::HEARTS) printf("♥");
        if (suit == Models::Suit::SPADES) printf("♠");
        printf("]");
        if (sep) printf(" ");
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

        std::vector<Models::BasePlayer*> winners;

        printf("\033[H\033[J");
        printf("+---------------+---------+---------+-----------+\n");
        printf("| Name:         | score:  | bet:    | cards:    |\n");
        printf("+---------------+---------+---------+-----------+\n");
        for (const auto& player : players) {
            printf("|%15s| %6u$ | %6u$ |", player->GetName(), player->GetBalance(), player->GetBet());
//            if ( !player->IsBot() ) {
            if (true) {
                auto hand = player->GetHand();
                PrintCard(hand.first, true);
                PrintCard(hand.second);
                printf("|");
            }
            else {
                printf("         |");
            }
            printf("\n+---------------+---------+---------+-----------+\n");
            if (player->GetWinner()) winners.push_back(player);
        }
        printf("\nBank: %u", board->GetPool());
        printf("\nTable Cards: ");
        for (const auto& card : board->GetCards()) {
            PrintCard(card);
            printf(" ");
        }
        if (!winners.empty()) {
            printf("\n");
            printf("*-----------------------------------------------------------*\n");
            printf("| Winners:                                                  |\n");

            std::vector<Models::Card> board_cards = board->GetCards();
            for (const auto& winner : winners) {
                printf("| Combination: %44s |\n", winner->GetCombination());
                std::pair<Models::Card, Models::Card> hand = winner->GetHand();
                printf("| ");
                PrintCard(hand.first, true);
                PrintCard(hand.second, true);
                for (const auto& board_card : board_cards) PrintCard(board_card, true);
                printf("%15s |\n", winner->GetName());
                printf("|                                                           |\n");
            }
            printf("*-----------------------------------------------------------*\n");
        }
        printf("\n\n");
    }
}