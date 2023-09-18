#include "hand.hh"
#include <QDebug>

Hand::Hand(Deck& deck):
    deck_(deck)
{
}

Hand::~Hand()
{
}

bool Hand::initial_draw() {
    // Return false until both cards of the initial draw has been dealt
    if(!draw_new_card()) {
        return false;
    }

    else if(deck_.get_deck_size()==0) {
        return false;
    }
    /* If hand size is 1, then the last card has been drawn from deck during
       the initial draw. Draw then 1 card more and return true, as now both
       of the 2 cards of the initial draw has been dealt
    */
    if(hand_.size()==1) {
        draw_new_card();
    }
    return true;
}

bool Hand::draw_new_card() {
    if(deck_.get_deck_size()==0) {
        return false;
    }
    std::unique_ptr<Card> card = deck_.draw_card();
    hand_.push_back(std::move(card));
    return true;
}

const std::vector<std::unique_ptr<Card>>& Hand::get_hand() const {
    return hand_;
}

int Hand::calculate_points() const{
    int total_points = 0;
    int ace_count = 0;

    for (const auto& card : hand_) {
        int card_points = card->get_points();
        total_points += card_points;
        if (card_points == ACE_POINTS) {
            ace_count++;
        }
    }

    // Adjust points if aces found and points go over 21
    while (total_points > BLACKJACK_THRESHOLD and ace_count > 0) {
        total_points -= (ACE_POINTS - 1);
        ace_count--;
    }

    return total_points;
}

int Hand::calculate_secondary_points() const {
    int ace_count = 0;
    int total_points = 0;

    for (const auto& card : hand_) {
        int card_points = card->get_points();
        total_points += card_points;
        if (card_points == ACE_POINTS) {
            ace_count++;
        }
    }

    /* If one ace is dealt and points are less than 21,
       then return the points where the value of the ace is 1
       These points will become the secondary points of the player
    */
    if (ace_count > 0 and total_points < BLACKJACK_THRESHOLD) {
        return total_points-(ACE_POINTS-1);
    }

    // Otherwise return the normal points
    return calculate_points();
}

void Hand::empty_hand() {
    hand_.clear();
}







