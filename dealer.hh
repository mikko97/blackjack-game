#ifndef DEALER_HH
#define DEALER_HH

#include <hand.hh>

#include <iostream>

class Dealer
{
public:

    /**
     * @brief Dealer constructor
     */
    Dealer(Deck& deck);

    /**
     * @brief Dealer destructor
     */
    ~Dealer();

    /**
     * @brief Initial draw of the first 2 cards
     */
    void initial_draw();

    /**
     * @brief Draw 1 additional card
     */
    void draw_new_card();

    /**
     * @brief Make the move after the initial draw of cards
     * @return The points of the hand after the move
     */
    void make_move();

    /**
     * @brief Get the hand which holds the current cards dealt
     * @return The hand of the dealer
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

    /**
     * @brief Get the points of the cards in hand
     * @return The points
     */
    int get_points() const;

    /**
     * @brief Empty the hand
     */
    void empty_hand();

    /**
     * @brief Reset the deck
     */
    void reset_deck();

private:
    std::unique_ptr<Hand> hand_;
};

#endif // DEALER_HH
