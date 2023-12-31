#include "headers/card.hh"

Card::Card(int value, int suit): value_(value), suit_(suit)
{
}

Card::~Card()
{
}

int Card::get_value() const {
    return value_;
}

int Card::get_suit() const {
    return suit_;
}

int Card::get_points() const {
    if (value_ == 1) {
        return 11;  // Ace
    } else if (value_ >= 2 and value_ <= 10) {
        return value_;  // Normal cards from 2 to 10
    } else {
        return 10;  // Jack, queen and king
    }
}
