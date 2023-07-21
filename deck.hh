#ifndef DECK_HH
#define DECK_HH

#include <card.hh>

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>

const int DECK_SIZE = 52;

class Deck
{
public:
    /**
     * @brief Deck constructor
     */
    Deck();

    /**
     * @brief Deck destructor
     */
    ~Deck();

    /**
     * @brief Shuffle the deck of cards
     */
    void shuffle();

    /**
     * @brief Draw a card from the deck
     * @return The card
     */
    std::unique_ptr<Card> draw_card();

    /**
     * @brief Create a new deck and shuffle it
     */
    void new_deck();

    /**
     * @brief Get the deck of cards
     * @return Reference to the vector containing the cards
     */
    std::vector<std::unique_ptr<Card>>& get_deck();

private:
    const int deck_size_ = DECK_SIZE;
    std::vector<std::unique_ptr<Card>> deck_;
};

#endif // DECK_HH
