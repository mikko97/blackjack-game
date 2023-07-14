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
     * @brief get_value
     * @return value of the card
     */
    int get_value() const;

    /**
     * @brief get_suit
     * @return suit of the card
     */
    int get_suit() const;

    /**
     * @brief get_points
     * @return Points of the card
     */
    int get_points() const;



private:
    int value_;
    int suit_;
};

#endif // CARD_HH
