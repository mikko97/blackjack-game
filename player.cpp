#include "player.hh"

Player::Player() : hand_(std::make_unique<Hand>())
{
}

void Player::initial_draw(std::vector<std::unique_ptr<Card>>& deck) {
    hand_->initial_draw(deck);
}

void Player::draw_new_card(std::vector<std::unique_ptr<Card>>& deck) {
    hand_->draw_new_card(deck);
}

const std::vector<std::unique_ptr<Card>>& Player::get_hand() const {
    return hand_->get_hand();
}

int Player::get_points() const {
    return hand_->calculate_points();
}
