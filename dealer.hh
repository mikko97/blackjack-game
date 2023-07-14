#ifndef DEALER_HH
#define DEALER_HH

#include <hand.hh>
#include <deck.hh>
#include <iostream>

class Dealer
{
public:

    /**
     * @brief Dealer constructor
     */
    Dealer();

    /**
     * @brief Dealer destructor
     */
    ~Dealer();

    /**
     * @brief initial_draw
     */
    void initial_draw(Deck& deck);

    /**
     * @brief draw_new_card
     */
    void draw_new_card(Deck& deck);

    /**
     * @brief make_move
     * @return The points of the hand
     */
    int make_move(Deck& deck);

    /**
     * @brief get_hand
     * @return The hand
     */
    const std::vector<Card*> get_hand();

private:
    Hand* hand_;
};

#endif // DEALER_HH
