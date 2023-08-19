#ifndef DECK_HH
#define DECK_HH

#include <card.hh>

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>


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
     * @return Pointer to the card object
     */
    std::unique_ptr<Card> draw_card();

    /**
     * @brief Create a new deck and shuffle it
     */
    void new_deck();

    /**
     * @brief Get the deck of cards
     * @return Reference to the vector containing the pointers to the card objects
     */
    std::vector<std::unique_ptr<Card>>& get_deck();

    /**
     * @brief Get the number of cards left in the deck
     * @return The number of cards left
     */
    int get_deck_size();

private:
    static const int DECK_SIZE = 52;
    static const int NUMBER_OF_DECKS = 5;
    std::vector<std::unique_ptr<Card>> deck_;
};

#endif // DECK_HH
