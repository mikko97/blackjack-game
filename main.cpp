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
    std::vector<std::unique_ptr<Card>>& deck_ref = deck->get_deck();

    // Diileri
    Dealer* dealer = new Dealer();
    dealer->initial_draw(deck_ref);
    int dealer_points = dealer->make_move(deck_ref);

    // Pelaaja
    Player* player = new Player();
    player->initial_draw(deck_ref);
    player->draw_new_card(deck_ref);
    player->draw_new_card(deck_ref);
    int player_points = player->get_points();

    if (dealer_points >= player_points) {
        std::cout << "Dealer's Hand:\n";
        for (const auto& card : dealer->get_hand()) {
            std::cout << "Suit: " << card->get_suit() << " Value: " << card->get_value() << std::endl;
        }
        std::cout << "Dealer's Points: " << dealer_points << std::endl;

        std::cout << "Player's Hand:\n";
        for (const auto& card : player->get_hand()) {
            std::cout << "Suit: " << card->get_suit() << " Value: " << card->get_value() << std::endl;
        }
        std::cout << "Player's Points: " << player_points << std::endl;

        std::cout << "Dealer wins!\n";
    } else {
        std::cout << "Dealer's Hand:\n";
        for (const auto& card : dealer->get_hand()) {
            std::cout << "Suit: " << card->get_suit() << " Value: " << card->get_value() << std::endl;
        }
        std::cout << "Dealer's Points: " << dealer_points << std::endl;

        std::cout << "Player's Hand:\n";
        for (const auto& card : player->get_hand()) {
            std::cout << "Suit: " << card->get_suit() << " Value: " << card->get_value() << std::endl;
        }
        std::cout << "Player's Points: " << player_points << std::endl;

        std::cout << "Player wins!\n";
    }


    return 0;

    //w.show();
    //return a.exec();
}
