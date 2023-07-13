#include "card.hh"

Card::Card(int value, int suit):
    value_(value), suit_(suit)
{
}

Card::~Card()
{
}

int Card::get_value() {
    return value_;
}

int Card::get_suit() {
    return suit_;
}
