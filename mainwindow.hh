#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "game.hh"
#include "account.hh"
#include "database.hh"
#include "statisticswindow.hh"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <qfile.h>
#include <QPropertyAnimation>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QFontDatabase>
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QTimer>
#include <thread>
#include <chrono>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Database *db, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /**
     * @brief Invoke a confirmation dialogue if user tries to close the app
     * @param QCloseEvent - i.e event invoken if user tries to close the app
     */
    void closeEvent(QCloseEvent *event) override;

private slots:

    /**
     * @brief Handles the event when the "New round" button is pressed
     *        to start the new round of blackjack.
     */
    void on_new_round_button_pressed();

    /**
     * @brief Start a new game.
     */
    //void reset_game();

    /**
     * @brief Handles the event when the "Hit" button is pressed
     *        to draw a card for the player.
     */
    void on_hit_button_pressed();

    /**
     * @brief Trigger the dealer's turn.
     */
    void dealer_turn();

    /**
     * @brief Handles the event when the "Withdraw" button is pressed
     *        to withdraw the money from the users account.
     */
    void on_withdraw_button_pressed();

    /**
     * @brief Handles the event when the "Statistics" button is pressed
     *        to open the statistics window.
     */
    void on_statistics_button_pressed();

private:
    /**
     * @brief Play the game
     */
    void play();

    /**
     * @brief Set the UI up for a new round
     */
    void set_up_UI();

    /**
     * @brief Set up players account
     */
    void set_up_account();

    /**
     * @brief Place the bet for the round
     */
    void place_bet();

    /**
     * @brief Update the images on the card image holders
     * @param Bool value if it's the players turn
     */
    void update_UI_cards(bool is_players_turn);

    /**
     * @brief Display players cards
     */
    void display_player_cards();

    /**
     * @brief Display dealers cards
     * @param Bool value if it's the players turn
     */
    void display_dealer_cards(bool is_players_turn);

    /**
     * @brief Animate the displaying of cards
     * @param card - card to be animated
     * @param end_pos - End position of the cards movement
     */
    void animate_card(QLabel* card, const QPoint& end_pos);

    /**
     * @brief Update the values and UI outputs relating to the game status
     */
    void update_UI_game_status();

    /**
     * @brief Update the values and UI outputs if player won
     */
    void update_UI_player_won(int player_score, int dealer_score);

    /**
     * @brief Update the values and UI outputs if dealer won
     */
    void update_UI_dealer_won(int player_score, int dealer_score);

    /**
     * @brief Data and UI related updates, that take place after every round
     */
    void updates_after_round(bool player_won);

    /**
     * @brief Update the values and UI outputs if game is tie
     */
    void update_UI_tie();

    /**
     * @brief Update the values and UI outputs if game is ongoing
     */
    void update_UI_ongoing(int player_score, int player_secondary_score);

    /**
     * @brief Update the players balance shown on UI
     */
    void update_UI_balance();

    /**
     * @brief Switch the enabled states of buttons
     * @param enable - Bool value whether to enable or disable a button
     * @param button_names - Vector of names of buttons, which states will be switched
     */
    void switch_button_enabled(bool enable, std::vector<std::string> button_names);

    /**
     * @brief Load the images from the resources
     * @param File path to the images
     * @return File path to the images
     */
    QPixmap load_pixmap_from_resource(const QString& file_path);

    /**
     * @brief Crop the image of the deck to simulate the gradual diminishing
     *        of the deck during the game.
     */
    void crop_deck_image();

    Database *m_db;
    Ui::MainWindow *ui;

    QVector<QPushButton*> buttons_;
    QPushButton* hit_button_;
    QPushButton* stay_button_;
    QPushButton* new_round_button_;
    QPushButton* statistics_button_;
    QPushButton* withdraw_money_button_;
    QTextBrowser* textbox1_;
    QTextBrowser* textbox2_;

    QPixmap deck_pixmap_;
    QLabel* deck_holder_;
    QVector<QLabel*> dealer_card_holders_;
    QVector<QPoint> dealer_card_positions_;
    QVector<QLabel*> player_card_holders_;
    QVector<QPoint> player_card_positions_;
    std::vector<bool> are_player_cards_animated_;
    std::vector<bool> are_dealer_cards_animated_;

    int bet_;
    int cards_left_ = 260;

    static const int NUM_CARD_HOLDERS = 10;
    static const int CARD_HOLDER_WIDTH = 200;
    static const int CARD_HOLDER_HEIGHT = 300;
    static const int BUTTON_WIDTH = 200;
    static const int BUTTON_HEIGHT = 100;
    static const int BLACKJACK_THRESHOLD = 21;

    inline static const QString GAME_INSTRUCTION = "\n\nPress 'Hit' to draw new card\nPress 'Stay' to stay";
    inline static const QString NEW_ROUND_INSTRUCTION = "Press the 'New round'-button to start the game";
    inline static const QString PLAYER_WON = "You won!\n";
    inline static const QString PLAYER_GOT_BLACKJACK = "You got blackjack!\n";
    inline static const QString PLAYER_WENT_BUST = "You went bust!";
    inline static const QString DEALER_WON = "Dealer won! \n";
    inline static const QString DEALER_GOT_BLACKJACK = "Dealer got blackjack!\n";
    inline static const QString DEALER_WENT_BUST = "Dealer went bust!";
    inline static const QString BOTH_GOT_BLACKJACK = "You both got blackjack!\n";
    inline static const QString GAME_IS_TIE = "It's a tie!\nYou both got blackjack!";
    inline static const QString ACCOUNT_DEPOSIT = "Enter money to your account";
    inline static const QString PLACE_BET = "Place your bet";



    Game game_;
    Account account_;
    StatisticsWindow statistics_window_;

};
#endif // MAINWINDOW_HH
