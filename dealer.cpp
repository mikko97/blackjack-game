#include "dealer.hh"

Dealer::Dealer(Deck& deck) : hand_(std::make_unique<Hand>(deck))
{

}

Dealer::~Dealer()
{
}

void Dealer::initial_draw() {
    hand_->initial_draw();
}

void Dealer::draw_new_card() {
    hand_->draw_new_card();
}

void Dealer::make_move() {
    while(hand_->calculate_points()<DEALER_THRESHOLD) {
        draw_new_card();
    }
}

const std::vector<std::unique_ptr<Card>>& Dealer::get_hand() const {
    return hand_->get_hand();
}

int Dealer::get_points() const {
    //return hand_->calculate_points();
    return 21;
}

void Dealer::empty_hand() {
    hand_->empty_hand();
}
