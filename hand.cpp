#include "hand.hh"

Hand::Hand(Deck& deck):
    deck_(deck)
{
}

Hand::~Hand()
{
}

void Hand::initial_draw() {
    draw_new_card();
    draw_new_card();
}

void Hand::draw_new_card() {
    std::unique_ptr<Card> card = deck_.draw_card();
    hand_.push_back(std::move(card));
}

const std::vector<std::unique_ptr<Card>>& Hand::get_hand() const {
    return hand_;
}

int Hand::calculate_points() const{
    int ace_count = 0;
    int total_points = 0;

    for (const auto& card : hand_) {
        int card_points = card->get_points();
        total_points += card_points;
        if (card_points == 11) {
            ace_count++;
        }
    }

    if (ace_count > 0 and total_points > 21) {
        total_points -= 10;
    }

    return total_points;
}

int Hand::calculate_secondary_points() const {
    int ace_count = 0;
    int total_points = 0;

    for (const auto& card : hand_) {
        int card_points = card->get_points();
        total_points += card_points;
        if (card_points == 11) {
            ace_count++;
        }
    }

    if (ace_count > 0 and total_points < 22) {
        return total_points-10;
    }
    return calculate_points();
}

void Hand::empty_hand() {
    hand_.clear();
}







