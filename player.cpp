#include "player.hh"

Player::Player()
{
    hand_ = new Hand();
}

Player::~Player()
{
    delete hand_;
}

void Player::initial_draw(Deck& deck) {
    hand_->initial_draw(deck);
}

void Player::draw_new_card(Deck& deck) {
    hand_->draw_new_card(deck);
}

const std::vector<Card*> Player::get_hand() {
    return hand_->get_hand();
}

int Player::get_points() {
    return hand_->calculate_points();
}
