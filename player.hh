#ifndef PLAYER_HH
#define PLAYER_HH

#include <hand.hh>
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
    void initial_draw(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief draw_new_card
     */
    void draw_new_card(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief get_hand
     * @return The hand
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

    /**
     * @brief get_points
     * @return The points of the hand
     */
    int get_points() const;

private:
    std::unique_ptr<Hand> hand_;
};

#endif // PLAYER_HH
