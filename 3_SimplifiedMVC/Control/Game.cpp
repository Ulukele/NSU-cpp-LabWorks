#include "Game.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <random>
#include "../Models/HumanPlayer.h"
#include "../Models/EquityBotPlayer.h"
#include "../View/Screen.h"
#include "../Common/Common.h"
#include "../Common/Exception.h"

namespace {
    bool CheckBet(Models::BasePlayer* player, Models::Bet bet, unsigned int last_bet) {

        if (bet.action == Models::Action::FOLD) return true;
        return bet.value <= player->GetBalance() + player->GetBet() && bet.value >= last_bet;
    }

}

namespace Control {
    Game::Game(unsigned int num_bots, unsigned int num_playable, unsigned int start_balance) {
        unsigned int num_players = num_bots + num_playable;
        if (num_players < 2u || num_players > 6u) {
            throw Exception::Exception("Invalid number of players, should be from 2 to 6");
        }

        for (int i = 0; i < num_playable; ++i) {
            auto *main_player = new Models::HumanPlayer(start_balance, i, "User " + std::to_string(i + 1));
            players.push_back(main_player);
        }

        for (int i = 0; i < num_bots; ++i) {
            auto* player = new Models::EquityBotPlayer(start_balance, num_playable + i, "Bot " + std::to_string(i + 1));
            players.push_back(player);
        }

        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(players.begin(), players.end(), generator);


        state = State::END;
        board = new Models::Board();

        View::Screen::Instance().Init(players, board);
    }

    void Game::InitPlayers() {
        for (const auto& player : players) {
            if (player->GetBalance()) {

            }
            player->SetHand(PickOne(), PickOne());
            player->SetPlaying(true);
            player->SetWinner(false);
        }
    }

    void Game::Start() {

        while (true) {
            unsigned int can_play = 0;
            for (const auto &player : players) {
                if (player->GetBalance() > 0) can_play++;
            }
            if (can_play < 2) break;
            StartRound();
            printf("Press ENTER to continue...");
            std::cin.ignore();
            std::cin.get();
        }
    }

    void Game::StartRound() {
        state = State::FLOP;
        board->Clear();
        Common::FillDeck(deck);
        InitPlayers();

        bool round_ended = false;
        while (!round_ended) {
            round_ended = ContinueRound();
        }
        JudgeRound();
    }

    void Game::JudgeRound() {
        if (state != State::END) throw Exception::Exception("Round hasn't ended, can't judge");

        std::pair<int, int> max_comb_level = std::make_pair(0, 0);
        std::vector<std::pair<int, int>> combinations_levels;
        for (const auto& player : players) {
            if (!player->GetPlaying()) {
                combinations_levels.emplace_back(-1, 0);
                continue;
            }
            // Create combination from cards on board and player hand
            std::vector<Models::Card> comb(board->GetCards());

            const std::pair<Models::Card, Models::Card> hand = player->GetHand();
            comb.push_back(hand.first);
            comb.push_back(hand.second);

            std::pair<int, int> comb_level = Common::GetCombinationLevel(comb);
            combinations_levels.push_back(comb_level);
            if (comb_level > max_comb_level) {
                max_comb_level = comb_level;
            }
            player->SetCombinationLevel(comb_level.first);
        }

        unsigned int winners_count = 0;
        for (int i = 0; i < players.size(); ++i) {
            if (combinations_levels[i] == max_comb_level && players[i]->GetPlaying()) {
                players[i]->SetWinner(true);
                winners_count++;
            }
        }
        if (winners_count == 0) return;
        unsigned int pool_part = board->GetPool() / winners_count;
        board->NullPool();
        for (const auto& player : players) {
            if (player->GetWinner()) player->RaiseBalance(pool_part);
        }
    }

    void Game::RefreshPlayersProb() {
        for (const auto& player : players) {
            double prob = Common::GetCombinationProbability(
                    player->GetHand(),
                    board->GetCards(),
                    (int)players.size());
            player->SetProb(prob);
        }
    }

    void Game::ProcessPlayersActions(unsigned int init_bet) {
        std::vector<unsigned int> bets(players.size(), 0);
        unsigned int last_bet = init_bet;
        board->SetLastBet(last_bet);
        for (const auto& player : players) {
            if (!player->GetPlaying()) continue;

            Models::Bet bet{Models::Action::FOLD, 0};
            if (player->GetBalance() + player->GetBet() < last_bet) continue;

            if (player->IsBot()) {
                bet = player->MakeDecision(board->GetCards(), last_bet, players.size());
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
                    if (CheckBet(player, bet, last_bet)) break;
                    player->TriggerUpdate();
                }
            }
            if (!CheckBet(player, bet, last_bet)) {
                bet = {Models::Action::FOLD, 0};
            }
            if (bet.action == Models::Action::FOLD) {
                player->SetPlaying(false);
            }
            else {
                bool status = player->MakeBet(bet.value);
                if (!status) throw Exception::Exception("Can't make bet");
                last_bet = bet.value;
                board->SetLastBet(last_bet);
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
        RefreshPlayersProb();

        unsigned int last_bet = 0;
        while (true) {
            ProcessPlayersActions(last_bet);
            std::vector<unsigned int> bets;
            unsigned int max_bet = 0;
            for (const auto& player : players) {
                max_bet = std::max(max_bet, player->GetBet());
            }
            last_bet = max_bet;
            bool again = false;
            for (const auto& player : players) {
                if (player->GetPlaying() && player->GetBet() < max_bet) again = true;
            }
            if (!again) break;
        }

        for (const auto& player : players) {
            board->RaisePool(player->SendBet());
        }
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

    unsigned int Game::GetPlayingCount() {
        unsigned int playing = 0;
        for (const auto& player : players) {
            if (player->GetPlaying()) playing++;
        }
        return playing;
    }
}