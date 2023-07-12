#include "card.hh"

Card::Card(int value, std::string suit):
    value_(value), suit_(suit)
{
}

Card::~Card()
{
}

int Card::get_value() {
    return value_;
}

std::string Card::get_suit() {
    return suit_;
}
