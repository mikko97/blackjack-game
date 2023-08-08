#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <game.hh>

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <qfile.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    /**
     * @brief Start a new round
     */
    void new_round();

    /**
     * @brief Start a new game
     */
    void reset_game();

    /**
     * @brief Trigger the player's turn
     */
    void player_hit();

    /**
     * @brief Trigger the dealer's turn
     */
    void dealer_turn();

    /**
     * @brief Play the game
     */
    void play();

private:

    void set_up_UI();
    void update_UI(bool first_round);
    QPixmap load_pixmap_from_resource(const QString& file_path);

    Ui::MainWindow *ui;
    QPushButton* hit_button_;
    QPushButton* stay_button_;
    QPushButton* reset_button_;
    QTextBrowser* textbox1_;
    QPushButton* new_round_button_;

    QList<QLabel*> player_card_holders_;
    QList<QLabel*> dealer_card_holders_;

    bool player_over_ = false;
    bool dealer_over_ = false;

    static const int NUM_CARD_HOLDERS = 10;
    static const int CARD_HOLDER_WIDTH = 200;
    static const int CARD_HOLDER_HEIGHT = 300;
    static const int BUTTON_WIDTH = 200;
    static const int BUTTON_HEIGHT = 100;
    static const int BLACKJACK_THRESHOLD = 21;

    Game game_;

};
#endif // MAINWINDOW_HH
