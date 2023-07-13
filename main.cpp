#include "mainwindow.hh"
#include "deck.hh"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    Deck* deck = new Deck();
    deck->shuffle();

    for(int i = 1; i <= 55; i++) {
        Card* card = deck->draw_card();
        if (card==nullptr) {
            std::cout << "EMPTY DECK" << std::endl;
        }
        else {
            std::cout << "Suit: " << card->get_suit() << ", " << "Value: " << card->get_value();
            std::cout << std::endl;
        }
    }

    return 0;

    //w.show();
    //return a.exec();
}
