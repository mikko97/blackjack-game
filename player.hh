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
    Player(Deck& deck);

    /**
     * @brief Player destructor
     */
    ~Player();

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
     * @return The hand of the player
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

    /**
     * @brief Get the points of the cards in hand
     * @return The points
     */
    int get_points() const;

    /**
     * @brief Get the points of the cards in hand
     * @return The points
     */
    int get_secondary_points() const;

    /**
     * @brief Empty hand
     */
    void empty_hand();

private:
    std::unique_ptr<Hand> hand_;
};

#endif // PLAYER_HH
