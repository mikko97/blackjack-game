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
     */
    Hand();

    /**
     * @brief Hand destructor
     */
    ~Hand();

    /**
     * @brief Draw the first 2 cards
     */
    void initial_draw(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief Draw additional cards
     */
    void draw_new_card(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief get_hand
     * @return The hand that includes the cards
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

    /**
     * @brief calculate_points
     * @return The points of the cards in the hand
     */
    int calculate_points() const;

private:
    std::vector<std::unique_ptr<Card>> hand_;
    int points_;
};

#endif // HAND_HH
