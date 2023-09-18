#include "headers/deck.hh"

Deck::Deck()
{
    new_deck();
}

void Deck::new_deck() {
    // Create the predetermined amount of decks and shuffle them
    deck_.clear();
    for(int i=1; i<=NUMBER_OF_DECKS; i++) {
        for (int suit = 1; suit <= SUITS_PER_DECK; suit++) {
            for (int value = 1; value <= CARDS_PER_SUIT; value++) {
                deck_.push_back(std::make_unique<Card>(value, suit));
            }
        }
    }
    shuffle();
}

Deck::~Deck()
{
}

void Deck::shuffle() {
    // Set random seed based on time to create different shuffles every time
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 g(static_cast<unsigned int>(seed));
    std::shuffle(deck_.begin(), deck_.end(), g);
}

std::unique_ptr<Card> Deck::draw_card() {
    std::unique_ptr<Card> card = std::move(deck_.back());
    deck_.pop_back();
    return card;
}

std::vector<std::unique_ptr<Card>>& Deck::get_deck() {
    return deck_;
}

int Deck::get_deck_size() {
    return deck_.size();
}

