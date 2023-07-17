#include "mainwindow.hh"
#include "deck.hh"
#include "dealer.hh"
#include "player.hh"

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

    Player* player = new Player();
    player->initial_draw(*deck);
    player->draw_new_card(*deck);

    int dealer_points = dealer->make_move(*deck);
    int player_points = player->get_points();

    if(dealer_points>=player_points) {
        for(auto card : dealer->get_hand()) {
            std::cout << " Dealer Suit: " << card->get_suit() << " Dealer Value: " << card->get_value() << std::endl;
        }
        for(auto card : player->get_hand()) {
            std::cout << " Player Suit: " << card->get_suit() << " Player Value: " << card->get_value() << std::endl;
        }
        std::cout << "Dealer Points: " << dealer_points << std::endl;
        std::cout << "Player Points: " << player_points << std::endl;
        std::cout << "Dealer wins!";
    }
    else {
        for(auto card : dealer->get_hand()) {
            std::cout << "Dealer Suit: " << card->get_suit() << " Dealer Value: " << card->get_value() << std::endl;
        }
        for(auto card : player->get_hand()) {
            std::cout << " Player Suit: " << card->get_suit() << " Player Value: " << card->get_value() << std::endl;
        }
        std::cout << "Dealer Points: " << dealer_points << std::endl;
        std::cout << "Player Points: " << player_points << std::endl;
        std::cout << "Player wins!";
    }

    delete deck;
    delete dealer;

    return 0;

    //w.show();
    //return a.exec();
}
