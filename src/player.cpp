#include "player.hh"

Player::Player(Deck& deck) : hand_(std::make_unique<Hand>(deck))
{

}

Player::~Player()
{
}

bool Player::initial_draw() {
    if(!hand_->initial_draw()) {
        return false;
    }
    return true;
}

bool Player::draw_new_card() {
    if(!hand_->draw_new_card()) {
        return false;
    }
    return true;
}

const std::vector<std::unique_ptr<Card>>& Player::get_hand() const {
    return hand_->get_hand();
}

int Player::get_points() const {
    return hand_->calculate_points();
}

int Player::get_secondary_points() const {
    return hand_->calculate_secondary_points();
}

void Player::empty_hand() {
    hand_->empty_hand();
}
