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
     * @brief draw_card
     * @return A card from the deck
     */
    std::unique_ptr<Card> draw_card();

    /**
     * @brief Create a new deck and shuffle it
     */
    void new_deck();

    /**
     * @brief Get the deck vector
     * @return Reference to the deck vector
     */
    std::vector<std::unique_ptr<Card>>& get_deck();

private:
    const int deck_size_ = DECK_SIZE;
    std::vector<std::unique_ptr<Card>> deck_;
};

#endif // DECK_HH
