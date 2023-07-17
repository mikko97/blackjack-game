#include "deck.hh"

Deck::Deck()
{
    new_deck();
}

void Deck::new_deck() {
    deck_.clear();
    for (int suit = 1; suit <= 4; suit++) {
        for (int value = 1; value <= 13; value++) {
            deck_.push_back(std::make_unique<Card>(value, suit));
        }
    }
    shuffle();
}

Deck::~Deck()
{
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck_.begin(), deck_.end(), g);
}

std::unique_ptr<Card> Deck::draw_card() {
    if (deck_.empty()) {
        new_deck();
    }

    std::unique_ptr<Card> card = std::move(deck_.back());
    deck_.pop_back();
    return card;
}

std::vector<std::unique_ptr<Card>>& Deck::get_deck() {
    return deck_;
}
