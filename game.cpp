#include "game.hh"
#include <algorithm>

Game::Game() :
    deck_(std::make_unique<Deck>()),player_(std::make_unique<Player>(*deck_)), dealer_(std::make_unique<Dealer>(*deck_))
{
}

Game::~Game()
{
}


void Game::new_round() {
    dealer_->empty_hand();
    player_->empty_hand();
    dealer_won_ = false;
    player_won_ = false;

    initial_draw();
}

void Game::initial_draw() {
    dealer_->initial_draw();
    player_->initial_draw();
}

void Game::dealer_turn() {
    dealer_->make_move();
    determine_winner();
}

void Game::player_hit() {
    player_->draw_new_card();
}

void Game::determine_winner() {
    if(dealer_->get_points()>=player_->get_points()) {
        dealer_won_ = true;
    }
    else {
        player_won_ = true;
    }
}

const std::vector<std::unique_ptr<Card>>& Game::get_player_hand() {
    return player_->get_hand();
}

const std::vector<std::unique_ptr<Card>>& Game::get_dealer_hand() {
    return dealer_->get_hand();
}

int Game::get_player_points() {
    return player_->get_points();
}

int Game::get_dealer_points() {
    return dealer_->get_points();
}

std::string Game::get_winner() {
    if(dealer_won_==true) {
        return "Dealer";
    }

    return "Player";
}

void Game::reset_game() {
    deck_ = std::make_unique<Deck>();
    player_ = std::make_unique<Player>(*deck_);
    dealer_ = std::make_unique<Dealer>(*deck_);
    dealer_won_ = false;
    player_won_ = false;
}



