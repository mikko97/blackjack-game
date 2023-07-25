#include "player.hh"

Player::Player(Deck& deck) : hand_(std::make_unique<Hand>(deck))
{

}

Player::~Player()
{
}

void Player::initial_draw() {
    hand_->initial_draw();
}

void Player::draw_new_card() {
    hand_->draw_new_card();
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
