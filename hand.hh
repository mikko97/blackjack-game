#ifndef HAND_HH
#define HAND_HH

#include <deck.hh>
#include <iostream>
#include <vector>

class Hand
{
public:
    /**
     * @brief Hand constructor
     */
    Hand();

    /**
     * @brief Hand destructor
     */
    ~Hand();

    /**
     * @brief Draw the first 2 cards
     */
    void initial_draw(Deck& deck);

    /**
     * @brief Draw additional cards
     */
    void draw_new_card(Deck& deck);

    /**
     * @brief get_hand
     * @return The hand that includes the cards
     */
    const std::vector<Card*>& get_hand();

    /**
     * @brief calculate_points
     * @return The points of the cards in the hand
     */
    int calculate_points();

private:
    std::vector<Card*> hand_;
    int points_;
};

#endif // HAND_HH
