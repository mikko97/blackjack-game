#ifndef HAND_HH
#define HAND_HH

#include <deck.hh>
#include <iostream>
#include <vector>
#include <memory>

class Hand
{
public:
    /**
     * @brief Hand constructor
     * @param Reference to the deck object
     */
    Hand(Deck& deck);

    /**
     * @brief Hand destructor
     */
    ~Hand();

    /**
     * @brief Initial draw of the first 2 cards
     */
    void initial_draw();

    /**
     * @brief Draw 1 additional card
     */
    void draw_new_card();

    /**
     * @brief Get the hand which holds the current cards dealt
     * @return Reference to the vector containing the pointers to the card objects
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

    /**
     * @brief Calculate the points of the cards in hand
     * @return The points
     */
    int calculate_points() const;

    /**
     * @brief Calculate secondary points of the cards in hand
     * @return The points
     */
    int calculate_secondary_points() const;

    /**
     * @brief Empty the hand
     */
    void empty_hand();

private:
    Deck& deck_;
    std::vector<std::unique_ptr<Card>> hand_;
    static const int BLACKJACK_THRESHOLD = 21;
    static const int ACE_POINTS = 11;
};

#endif // HAND_HH
