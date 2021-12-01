#include "Game.h"

#include <string>
#include <algorithm>
#include <random>
#include "../Models/HumanPlayer.h"
#include "../Models/EquityBotPlayer.h"
#include "../View/Screen.h"


namespace {
    void FillDeck(std::vector<Models::Card>& deck) {
        deck.resize(0);
        for (unsigned short i = 2; i < 15u; ++i ) {
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
        FillDeck(deck);
        InitPlayers();

        bool round_ended = false;
        while (!round_ended) {
            round_ended = ContinueRound();
        }
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