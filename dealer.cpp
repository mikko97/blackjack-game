#include "dealer.hh"
Dealer::Dealer()
{
    hand_ = new Hand();
}

Dealer::~Dealer()
{
    delete hand_;
}

void Dealer::initial_draw(Deck& deck) {
    hand_->initial_draw(deck);
}

void Dealer::draw_new_card(Deck& deck) {
    hand_->draw_new_card(deck);
}

int Dealer::make_move(Deck& deck) {
    while(hand_->calculate_points()<17) {
        draw_new_card(deck);
    }

    return hand_->calculate_points();
}

const std::vector<Card*> Dealer::get_hand() {
    return hand_->get_hand();
}
