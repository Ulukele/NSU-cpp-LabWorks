#include "Game.h"

#include <string>
#include <algorithm>
#include <random>
#include "../Models/HumanPlayer.h"
#include "../Models/EquityBotPlayer.h"
#include "../View/Screen.h"


namespace {
    const unsigned int MAX_VALUES = 15u;
    const unsigned int MIN_VALUE = 2u;
    const unsigned int MAX_SUITS = 4u;

    void FillDeck(std::vector<Models::Card>& deck) {
        deck.resize(0);
        for (unsigned short i = MIN_VALUE; i < MAX_VALUES; ++i ) {
            deck.push_back(Models::Card{Models::Suit::SPADES, i});
            deck.push_back(Models::Card{Models::Suit::HEARTS, i});
            deck.push_back(Models::Card{Models::Suit::DIAMONDS, i});
            deck.push_back(Models::Card{Models::Suit::CLUBS, i});
        }

        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(deck.begin(), deck.end(), generator);
    }
    bool CheckBet(Models::BasePlayer* player, Models::Bet bet) {
        if (bet.action == Models::Action::FOLD) return true;
        return bet.value <= player->GetBalance();
    }

    const char* COMBINATIONS[] = {
            "High card",
            "One Pair",
            "Two Pairs",
            "Three of a kind",
            "Straight",
            "Flush",
            "Full house",
            "Four of a kind",
            "Straight flush",
            "Royal flush"
    };
    std::pair<int, int> GetCombinationLevel(const std::vector<Models::Card>& cards) {
        int comb = 0;
        int senior_card = 0;
        for (const auto& card: cards) {
            if (senior_card < card.value) senior_card = card.value;
        }

        size_t len = cards.size();

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
            if (cards_suit >= 5) comb = std::max(comb, 5);;
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
}

namespace Control {
    Game::Game(unsigned int num_players, unsigned int start_balance) {
        if (num_players < 2u || num_players > 6u) {
            throw; //TODO: exception
        }

        auto* main_player = new Models::HumanPlayer(start_balance, "User");
        players.push_back(main_player);

        for (int i = 0; i < num_players - 1; ++i) {
            auto* player = new Models::EquityBotPlayer(start_balance, "Bot");
            players.push_back(player);
        }
        state = State::END;
        board = new Models::Board();

        View::Screen::Instance().Init(players, board);
    }

    void Game::InitPlayers() {
        for (const auto& player : players) {
            player->SetHand(PickOne(), PickOne());
            player->SetPlaying(true);
        }
    }

    void Game::Start() {
        state = State::FLOP;
        board->Clear();
        FillDeck(deck);
        InitPlayers();

        bool round_ended = false;
        while (!round_ended) {
            round_ended = ContinueRound();
        }
    }

    void Game::JudgeRound() {
        if (state != State::END) throw; // TODO

        std::pair<int, int> max_comb_level = std::make_pair(0, 0);
        std::vector<std::pair<int, int>> combinations_levels;
        for (const auto& player : players) {
            // Create combination from cards on board and player hand
            std::vector<Models::Card> comb(board->GetCards());
            const std::pair<Models::Card, Models::Card> hand = player->GetHand();
            comb.push_back(hand.first);
            comb.push_back(hand.second);

            std::pair<int, int> comb_level = GetCombinationLevel(comb);
            combinations_levels.push_back(comb_level);
            if (comb_level > max_comb_level) {
                max_comb_level = comb_level;
            }
        }

        std::vector<Models::BasePlayer*> winners;
        std::vector< std::vector<Models::Card> > combinations;
        for (int i = 0; i < players.size(); ++i) {
            if (combinations_levels[i] == max_comb_level) {
                winners.push_back(players[i]);

                // Create combination from cards on board and player hand
                std::vector<Models::Card> comb(board->GetCards());
                const std::pair<Models::Card, Models::Card> hand = players[i]->GetHand();
                comb.push_back(hand.first);
                comb.push_back(hand.second);

                combinations.push_back(comb);
            }
        }
        board->ProcessWinners(winners, combinations);
    }

    void Game::ProcessPlayersActions() {
        std::vector<unsigned int> bets(players.size(), 0);
        unsigned int last_bet = 0;
        for (const auto& player : players) {
            if (!player->GetPlaying()) continue;
            Models::Bet bet{Models::Action::FOLD, 0};
            if (player->IsBot()) {
                bet = player->MakeDecision(board->GetCards(), bets);
            }
            else {
                while (true) {
                    int value;
                    printf("\n> Choose bet (-1 for fold): ");
                    scanf("%d", &value);
                    if (value == -1) {
                        bet = {Models::Action::FOLD, 0};
                    } else {
                        bet = {Models::Action::RAISE, (unsigned int) value};
                    }
                    if (CheckBet(player, bet)) break;
                }
            }
            if (bet.action == Models::Action::FOLD) {
                player->SetPlaying(false);
            }
            else {
                player->MakeBet(bet.value);
            }
        }

        for (const auto& player : players) {
            board->RaisePool(player->SendBet());
        }
    }

    bool Game::ContinueRound() {
        if (state == State::FLOP) {
            for (int i = 0; i < 3; ++i) {
                board->AddCard(PickOne());
            }
            state = State::TURN;
        }
        else if (state == State::TURN) {
            board->AddCard(PickOne());
            state = State::RIVER;
        }
        else if (state == State::RIVER) {
            board->AddCard(PickOne());
            state = State::END;
        }
        else { // Round ended
            return true;
        }
        ProcessPlayersActions();
        return false;
    }

    Game::~Game() {
        for (const auto& player : players) {
            delete player;
        }
        delete board;
    }

    Models::Card Game::PickOne() {
        Models::Card card = deck.back();
        deck.pop_back();
        return card;
    }
}