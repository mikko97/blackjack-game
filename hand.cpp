#include "hand.hh"
#include "deck.hh"

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::initial_draw(Deck& deck) {
    Card* first_card = deck.draw_card();
    Card* second_card = deck.draw_card();
    hand_.push_back(first_card);
    hand_.push_back(second_card);
}

void Hand::draw_new_card(Deck& deck) {
    Card* card = deck.draw_card();
    hand_.push_back(card);
}

const std::vector<Card*>& Hand::get_hand() {
    return hand_;
}

int Hand::calculate_points() {
    int total_points  = 0;
    int ace_count = 0;

    for (Card* card : hand_) {
        int card_points = card->get_points();
        total_points += card_points;
        if (card_points == 1) {
            ace_count++;
        }
    }

    if (ace_count > 0 and total_points + 10 <= 21) {
        total_points += 10;
    }

    return total_points;
}
