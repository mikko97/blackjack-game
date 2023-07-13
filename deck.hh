#ifndef DECK_HH
#define DECK_HH

#include <card.hh>

#include <iostream>
#include <vector>

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
    Card* draw_card();

    /**
     * @brief Create a new deck and shuffle it
     */
    void new_deck();

private:
    const int deck_size_ = DECK_SIZE;
    std::vector<Card*> deck_;
};

#endif // DECK_HH
