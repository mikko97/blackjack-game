#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "game.hh"
#include "account.hh"
#include "database.hh"
#include "statisticswindow.hh"
#include "ui_statisticswindow.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <qfile.h>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Database *db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    /**
     * @brief Start a new round
     */
    void new_round();

    /**
     * @brief Start a new game
     */
    //void reset_game();

    /**
     * @brief Trigger the player's turn
     */
    void player_hit();

    /**
     * @brief Trigger the dealer's turn
     */
    void dealer_turn();

    /**
     * @brief Take the money
     */
    void take_money();

    /**
     * @brief Open the statistics window
     */
    void open_stats_window();

private:
    Database *m_db;

    /**
     * @brief Set up players account
     */
    void set_up_account();

    /**
     * @brief Place the bet for the round
     */
    void place_bet();

    /**
     * @brief Play the game
     */
    void play();

    /**
     * @brief Set the UI up for a new round
     */
    void set_up_UI();

    /**
     * @brief Update the images on the card image holders
     * @param Bool value if it's the players turn
     */
    void update_UI_cards(bool is_players_turn);

    /**
     * @brief Update the values and UI outputs relating to the game status
     */
    void update_UI_game_status();

    /**
     * @brief Update the players balance shown on UI
     */
    void update_UI_balance();

    /**
     * @brief Load the images from the resources
     */
    QPixmap load_pixmap_from_resource(const QString& file_path);

    Ui::MainWindow *ui;
    QPushButton* hit_button_;
    QPushButton* stay_button_;
    //QPushButton* reset_button_;
    QPushButton* new_round_button_;
    QPushButton* stat_button_;
    QPushButton* take_money_button_;
    QTextBrowser* textbox1_;
    QTextBrowser* textbox2_;

    QVector<QLabel*> dealer_card_holders_;
    QVector<QLabel*> player_card_holders_;
    QVector<QPoint> dealer_card_positions_;
    QVector<QPoint> player_card_positions_;

    int bet_;

    static const int NUM_CARD_HOLDERS = 10;
    static const int CARD_HOLDER_WIDTH = 200;
    static const int CARD_HOLDER_HEIGHT = 300;
    static const int BUTTON_WIDTH = 200;
    static const int BUTTON_HEIGHT = 100;
    static const int BLACKJACK_THRESHOLD = 21;

    Game game_;
    Account account_;
    StatisticsWindow statistics_window_;

};
#endif // MAINWINDOW_HH
