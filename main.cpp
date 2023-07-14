#include "mainwindow.hh"
#include "deck.hh"
#include "hand.hh"
#include "dealer.hh"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    Deck* deck = new Deck();
    deck->shuffle();

    Dealer* dealer = new Dealer();
    dealer->initial_draw(*deck);

    int dealer_points = dealer->make_move(*deck);
    if(dealer_points>10) {
        for(auto card : dealer->get_hand()) {
            std::cout << "Suit: " << card->get_suit() << " Value: " << card->get_value() << std::endl;
        }
        std::cout << "Points: " << dealer_points << std::endl;
        std::cout << "Dealer wins!";
    }
    else {
        for(auto card : dealer->get_hand()) {
            std::cout << "Suit: " << card->get_suit() << " Value: " << card->get_value() << std::endl;
        }
        std::cout << "Points: " << dealer_points << std::endl;
        std::cout << "Dealer wins!";
        std::cout << "Dealer loses!";
    }

    delete deck;
    delete dealer;

    return 0;

    //w.show();
    //return a.exec();
}
