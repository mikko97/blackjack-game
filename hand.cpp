#include "hand.hh"

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::initial_draw(std::vector<std::unique_ptr<Card>>& deck) {
    draw_new_card(deck);
    draw_new_card(deck);
}

void Hand::draw_new_card(std::vector<std::unique_ptr<Card>>& deck) {
    std::unique_ptr<Card> card = std::move(deck.back());
    deck.pop_back();
    hand_.push_back(std::move(card));
}

const std::vector<std::unique_ptr<Card>>& Hand::get_hand() const {
    return hand_;
}

int Hand::calculate_points() const {
    int total_points  = 0;
    int ace_count = 0;

    for (const auto& card : hand_) {
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
