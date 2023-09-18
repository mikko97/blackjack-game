#include "headers/dealer.hh"

Dealer::Dealer(Deck& deck) : hand_(std::make_unique<Hand>(deck))
{

}

Dealer::~Dealer()
{
}

bool Dealer::initial_draw() {
    if(!hand_->initial_draw()) {
        return false;
    }
    return true;
}

bool Dealer::draw_new_card() {
    if(!hand_->draw_new_card()) {
        return false;
    }
    return true;
}

bool Dealer::make_move() {
    // Draw cards until the dealers threshold to stay is reached
    while(hand_->calculate_points()<DEALER_THRESHOLD) {
        if(!draw_new_card()) {
            return false;
        }
    }
    return true;
}

const std::vector<std::unique_ptr<Card>>& Dealer::get_hand() const {
    return hand_->get_hand();
}

int Dealer::get_points() const {
    return hand_->calculate_points();
}

void Dealer::empty_hand() {
    hand_->empty_hand();
}
