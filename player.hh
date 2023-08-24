#ifndef PLAYER_HH
#define PLAYER_HH

#include <hand.hh>

class Player
{
public:

    /**
     * @brief Player constructor
     * @param Reference to the deck object
     */
    Player(Deck& deck);

    /**
     * @brief Player destructor
     */
    ~Player();

    /**
     * @brief Initial draw of the first 2 cards
     * @return Bool value if deck has 2 cards left to draw
     */
    bool initial_draw();

    /**
     * @brief Draw 1 additional card
     * @return Bool value if deck has cards left to draw
     */
    bool draw_new_card();

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
     * @brief Get the secondary points of the cards in hand when ace is dealt
     * @return The points
     */
    int get_secondary_points() const;

    /**
     * @brief Empty the hand
     */
    void empty_hand();

private:
    std::unique_ptr<Hand> hand_;
};

#endif // PLAYER_HH
