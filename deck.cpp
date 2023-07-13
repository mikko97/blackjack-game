#include "deck.hh"

Deck::Deck()
{
    new_deck();
}

void Deck::new_deck() {

    for (auto card : deck_) {
        delete card;
    }
    deck_.clear();

    for (int suit = 1; suit <= 4; suit++) {
        for (int value = 1; value <= 13; value++) {
            deck_.push_back(new Card(value, suit));
        }
    }
}

Deck::~Deck() {
    for(auto card : deck_) {
        delete card;
    }
}

void Deck::shuffle() {

    for(int i = 0; i < deck_size_; i++) {
        std::swap(deck_[i], deck_[rand()%deck_size_]);
    }
}

Card* Deck::draw_card() {

    if (deck_.empty()) {
        new_deck();
    }

    Card* card = deck_.back();
    deck_.pop_back();
    return card;
}

