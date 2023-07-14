#include "mainwindow.hh"
#include "deck.hh"
#include "hand.hh"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    Deck* deck = new Deck();
    deck->shuffle();

    Hand* hand = new Hand();
    hand->initial_draw(*deck);
    hand->draw_new_card(*deck);

    delete deck;

    // Print the suit and value of the cards in the hand
    std::cout << "Cards in Hand:" << std::endl;
    const std::vector<Card*>& cards = hand->get_hand();
    for (Card* card : cards) {
        std::cout << "Suit: " << card->get_suit() << ", Value: " << card->get_value() << std::endl;
    }
    std::cout << std::endl;

    int points = hand->calculate_points();

    std::cout << "Points: " << points << std::endl;

    delete hand;

    return 0;

    //w.show();
    //return a.exec();
}
