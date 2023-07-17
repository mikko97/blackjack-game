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
    void initial_draw(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief draw_new_card
     */
    void draw_new_card(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief make_move
     * @return The points of the hand
     */
    int make_move(std::vector<std::unique_ptr<Card>>& deck);

    /**
     * @brief get_hand
     * @return The hand
     */
    const std::vector<std::unique_ptr<Card>>& get_hand() const;

private:
    std::unique_ptr<Hand> hand_;
};

#endif // DEALER_HH
