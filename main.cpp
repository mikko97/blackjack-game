#include "mainwindow.hh"
#include "card.hh"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;

    Card* card = new Card(5, "Hearts");
    std::cout << "Value of card is: " << card->get_value() << std::endl;
    std::cout << "Suit of card is: " << card->get_suit() << std::endl;
    delete card;

    return 0;

    //w.show();
    //return a.exec();
}
