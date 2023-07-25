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
    dealer_won_ = false;
    dealer_over = false;

    player_->empty_hand();
    player_won_ = false; 
    player_over = false;

    tie_ = false;
    round_over_ = false;

    initial_draw();
}

void Game::initial_draw() {
    dealer_->initial_draw();
    player_->initial_draw();
    if(player_->get_points()==BLACKJACK_THRESHOLD and dealer_->get_points()==BLACKJACK_THRESHOLD) {
        tie_ = true;
        round_over_ = true;
    }
}

void Game::dealer_turn() {
    dealer_->make_move();
    if(dealer_->get_points()>BLACKJACK_THRESHOLD) {
        dealer_over = true;
    }
    determine_winner();
}

void Game::player_hit() {
    player_->draw_new_card();
    if(player_->get_points()>BLACKJACK_THRESHOLD) {
        player_over = true;
        determine_winner();
    }
}

void Game::determine_winner() {
    if(!round_over_) {
        if(player_over==true) {
            dealer_won_ = true;
        }
        else if(player_over==false and dealer_over==false and dealer_->get_points()>=player_->get_points()) {
            dealer_won_ = true;
        }
        else if(player_over==false and dealer_over==false and player_->get_points()>dealer_->get_points()) {
            player_won_ = true;
        }
        else if(player_over==false and dealer_over==true){
            player_won_ = true;
        }
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

int Game::get_player_secondary_points() {
    return player_->get_secondary_points();
}

int Game::get_dealer_points() {
    return dealer_->get_points();
}

std::string Game::get_winner() {
    if(dealer_won_==true) {
        return "Dealer";
    }
    else if(player_won_==true) {
        return "Player";
    }
    else if(tie_==true) {
        return "Tie";
    }
    return "Ongoing";
}

void Game::reset_game() {
    deck_ = std::make_unique<Deck>();
    player_ = std::make_unique<Player>(*deck_);
    dealer_ = std::make_unique<Dealer>(*deck_);
}



