#include "headers/game.hh"

Game::Game() :
    deck_(std::make_unique<Deck>()),
    player_(std::make_unique<Player>(*deck_)),
    dealer_(std::make_unique<Dealer>(*deck_))
{
}

Game::~Game()
{
}

void Game::new_round() {
    dealer_->empty_hand();
    player_->empty_hand();
    tie_ = false;
    round_over_ = false;
    dealer_won_ = false;
    player_won_ = false;
}

bool Game::new_round_player() {
    if(!player_->initial_draw()) {
        return false;
    }
    return true;
}

bool Game::new_round_dealer() {
    if(!dealer_->initial_draw()) {
        return false;
    }
    if(is_blackjack_player() and is_blackjack_dealer()) {
        tie_ = true;
        round_over_ = true;
    }
    else if(is_blackjack_player()) {
        player_won_ = true;
        round_over_ = true;
    }
    return true;
}

bool Game::dealer_turn() {
    if(!dealer_->make_move()) {
        return false;
    }
    determine_winner();
    return true;
}

bool Game::player_hit() {
    if(!player_->draw_new_card()) {
        return false;
    }
    if(is_player_over()) {
        determine_winner();
    }
    return true;
}

void Game::determine_winner() {
    if(!round_over_) {
        if(is_player_over()) {
            dealer_won_ = true;
        }
        else if(is_dealer_over()) {
            player_won_ = true;
        }
        else if(dealer_->get_points()>=player_->get_points()) {
            dealer_won_ = true;
        }
        else {
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

bool Game::is_blackjack_player() {
    if(player_->get_points()==BLACKJACK_THRESHOLD) {
        return true;
    }
    return false;
}

bool Game::is_blackjack_dealer() {
    if(dealer_->get_points()==BLACKJACK_THRESHOLD) {
        return true;
    }
    return false;
}

bool Game::is_player_over() {
    if(player_->get_points()>21) {
        return true;
    }
    return false;
}

bool Game::is_dealer_over() {
    if(dealer_->get_points()>21) {
        return true;
    }
    return false;
}

int Game::get_deck_size() {
    return deck_->get_deck_size();
}

void Game::create_new_deck() {
    deck_->new_deck();
}


