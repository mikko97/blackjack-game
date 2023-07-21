#ifndef CARD_HH
#define CARD_HH

#include <iostream>

class Card
{
public:

    /**
     * @brief Card constructor
     * @param value - value of the card
     * @param suit - suit of the card
     */
    Card(int value, int suit);

    /**
     * @brief Card destructor
     */
    ~Card();

    /**
     * @brief Get the value of the card
     * @return value of the card
     */
    int get_value() const;

    /**
     * @brief Get the suit of the card
     * @return suit of the card
     */
    int get_suit() const;

    /**
     * @brief Get the points of the card
     * @return Points of the card
     */
    int get_points() const;



private:
    int value_;
    int suit_;
};

#endif // CARD_HH
