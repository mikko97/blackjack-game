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
    Card(int value, std::string suit);

    /**
     * @brief Card destructor
     */
    ~Card();

    /**
     * @brief get_value
     * @return value of the card
     */
    int get_value();

    /**
     * @brief get_suit
     * @return suit of the card
     */
    std::string get_suit();



private:
    int value_;
    std::string suit_;
};

#endif // CARD_HH
