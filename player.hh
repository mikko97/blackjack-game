#ifndef PLAYER_HH
#define PLAYER_HH

#include <hand.hh>
#include <deck.hh>
#include <iostream>

class Player
{
public:

    /**
     * @brief Player constructor
     */
    Player();

    /**
     * @brief Player destructor
     */
    ~Player();

    /**
     * @brief initial_draw
     */
    void initial_draw(Deck& deck);

    /**
     * @brief draw_new_card
     */
    void draw_new_card(Deck& deck);

    /**
     * @brief get_hand
     * @return The hand
     */
    const std::vector<Card*> get_hand();

    /**
     * @brief get_points
     * @return The points of the hand
     */
    int get_points();

private:
    Hand* hand_;
};

#endif // PLAYER_HH
