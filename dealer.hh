#ifndef DEALER_HH
#define DEALER_HH

#include "hand.hh"

#include <iostream>

class Dealer
{
public:

    /**
     * @brief Dealer constructor
     * @param Reference to the deck object
     */
    Dealer(Deck& deck);

    /**
     * @brief Dealer destructor
     */
    ~Dealer();

    /**
     * @brief Initial draw of the first 2 cards
     * @return Bool value if deck has 2 cards left to draw
     */
    bool initial_draw();

    /**
     * @brief Draw 1 additional card
     * @return Bool value if deck has 2 cards left to draw
     */
    bool draw_new_card();

    /**
     * @brief Make the dealers moves after the initial draw of cards
     */
    bool make_move();

    /**
     * @brief Get the hand which holds the current cards dealt
     * @return Reference to the vector containing the pointers to the card objects
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

    /**
     * @brief Get the points of the cards in hand
     * @return The points
     */
    int get_points() const;

    /**
     * @brief Empty the dealers hand
     */
    void empty_hand();

private:
    std::unique_ptr<Hand> hand_;
    static const int DEALER_THRESHOLD = 17;
};

#endif // DEALER_HH
