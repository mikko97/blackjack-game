#include "dealer.hh"

Dealer::Dealer() : hand_(std::make_unique<Hand>())
{

}

Dealer::~Dealer()
{
}

void Dealer::initial_draw(std::vector<std::unique_ptr<Card>>& deck) {
    hand_->initial_draw(deck);
}

void Dealer::draw_new_card(std::vector<std::unique_ptr<Card>>& deck) {
    hand_->draw_new_card(deck);
}

int Dealer::make_move(std::vector<std::unique_ptr<Card>>& deck) {
    while(hand_->calculate_points()<17) {
        draw_new_card(deck);
    }

    return hand_->calculate_points();
}

const std::vector<std::unique_ptr<Card>>& Dealer::get_hand() const {
    return hand_->get_hand();
}
