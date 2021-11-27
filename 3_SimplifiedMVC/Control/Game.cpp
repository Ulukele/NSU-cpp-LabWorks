#include "Game.h"

#include <memory>
#include "string"


namespace Control {
    Game::Game(unsigned int num_players, unsigned int start_balance) {
        if (num_players < 2u || num_players > 6u) {
            throw; //TODO: exception
        }

        auto* main_player = new Models::HumanPlayer(start_balance, "User");
        players.push_back(main_player);

        for (int i = 0; i < num_players - 1; ++i) {
            auto* player = new Models::HumanPlayer(start_balance, ("Bot" + std::to_string(i)).c_str());
            players.push_back(player);
        }

        board = new Models::Board();
    }

    void Game::Start() {
        Round();
    }

    void Game::Round() {
        // TODO
    }

    Game::~Game() {
        for (const auto& player : players) {
            delete player;
        }
        delete board;
    }
}