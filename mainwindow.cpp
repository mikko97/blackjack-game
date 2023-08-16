#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "database.hh"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QTextBrowser>
#include <QFontDatabase>
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(Database *db, QWidget *parent) :
    QMainWindow(parent),
    m_db(db),
    ui(new Ui::MainWindow),
    account_(db),
    statistics_window_(db)
{

    QFont button_font1("Tahoma", 16, QFont::DemiBold);
    QFont button_font2("Tahoma", 12, QFont::DemiBold);
    QFont button_font3("Tahoma", 10, QFont::DemiBold);

    // Set up the main widget
    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Create the main layout for the central widget
    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);

    // Create the first group of frames
    QHBoxLayout* dealer_layout = new QHBoxLayout;
    for (int i = 0; i < NUM_CARD_HOLDERS; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(CARD_HOLDER_WIDTH, CARD_HOLDER_HEIGHT);
        label->setPixmap(QPixmap());

        dealer_layout->addWidget(label);
        dealer_card_holders_.append(label);
        dealer_card_positions_.append(label->pos());
    }

    // Create the second group of frames
    QHBoxLayout* player_layout = new QHBoxLayout;
    for (int i = 0; i < NUM_CARD_HOLDERS; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(CARD_HOLDER_WIDTH, CARD_HOLDER_HEIGHT);
        label->setPixmap(QPixmap());

        player_layout->addWidget(label);
        player_card_holders_.append(label);
        player_card_positions_.append(label->pos());
    }

    // Create a horizontal layout for the buttons
    QHBoxLayout* button_layout1 = new QHBoxLayout;

    // Add buttons to the button layout
    hit_button_ = new QPushButton("Hit", this);
    hit_button_->setObjectName("Hit");
    hit_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    hit_button_->setStyleSheet("background-color: green");
    hit_button_->setFont(button_font1);

    stay_button_ = new QPushButton("Stay", this);
    stay_button_->setObjectName("Stay");
    stay_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    stay_button_->setStyleSheet("background-color: red");
    stay_button_->setFont(button_font1);

    take_money_button_ = new QPushButton("Withdraw money", this);
    take_money_button_->setObjectName("Take");
    take_money_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    take_money_button_->setStyleSheet("background-color: yellow");
    take_money_button_->setFont(button_font3);

    button_layout1->addWidget(hit_button_);
    button_layout1->addWidget(stay_button_);
    button_layout1->addWidget(take_money_button_);
    button_layout1->addStretch(1);
    QHBoxLayout* button_layout2 = new QHBoxLayout;

    new_round_button_ = new QPushButton("New round", this);
    new_round_button_->setObjectName("New round");
    new_round_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    new_round_button_->setStyleSheet("background-color: white");
    new_round_button_->setFont(button_font2);

    /*reset_button_ = new QPushButton("Reset game", this);
    reset_button_->setObjectName("Reset game");
    reset_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    reset_button_->setStyleSheet("background-color: white");
    reset_button_->setFont(button_font2);
    */

    stat_button_ = new QPushButton("Stats", this);
    stat_button_->setObjectName("Stats");
    stat_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    stat_button_->setStyleSheet("background-color: white");
    stat_button_->setFont(button_font2);

    button_layout2->addWidget(new_round_button_);
    //button_layout2->addWidget(reset_button_);
    button_layout2->addWidget(stat_button_);
    button_layout2->addStretch(1);

    // Create a vertical layout
    QVBoxLayout* new_layout = new QVBoxLayout;
    QFont text_browser_font("Tahoma", 22);

    textbox1_ = new QTextBrowser();
    textbox1_->setStyleSheet("padding: 22px; color: white; border-style: dashed; border-width: 8px; border-color: white");
    textbox1_->setFont(text_browser_font);
    new_layout->addWidget(textbox1_);

    textbox2_ = new QTextBrowser();
    textbox2_->setStyleSheet("padding: 22px; color: white; border-style: dashed; border-width: 8px; border-color: white");
    textbox2_->setFont(text_browser_font);
    new_layout->addWidget(textbox2_);

    // Add the groups of frames to the main layout
    main_layout->addLayout(dealer_layout);
    main_layout->addLayout(player_layout);

    // Wrap button_layout1 and button_layout2 in a QVBoxLayout
    QVBoxLayout* buttons_layouts_container = new QVBoxLayout;
    buttons_layouts_container->addLayout(button_layout1);
    buttons_layouts_container->addLayout(button_layout2);

    // Create a horizontal layout to hold the new layout and button_layouts
    QHBoxLayout* right_layout = new QHBoxLayout;

    // Add the QVBoxLayout with button_layouts to the right_layout
    right_layout->addLayout(buttons_layouts_container);

    // Add the new_layout to the right_layout
    right_layout->addLayout(new_layout);

    // Add the right_layout to the main layout
    main_layout->addLayout(right_layout);

    // Set the main layout as the central widget's layout
    central_widget->setLayout(main_layout);
    central_widget->setStyleSheet("background-color: #008080");

    // Connecting slots
    connect(hit_button_, &QPushButton::clicked, this, &MainWindow::player_hit);
    connect(stay_button_, &QPushButton::clicked, this, &MainWindow::dealer_turn);
    connect(new_round_button_, &QPushButton::clicked, this, &MainWindow::new_round);
    //connect(reset_button_, &QPushButton::clicked, this, &MainWindow::reset_game);
    connect(take_money_button_, &QPushButton::clicked, this, &MainWindow::take_money);
    connect(stat_button_, &QPushButton::clicked, this, &MainWindow::open_stats_window);

    play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_up_account() {
    bool ok;
    int money = QInputDialog::getInt(nullptr, "Account", "Enter money to your account", 1, 10, 100, 1, &ok);

    if(ok) {
        account_.set_up_account(money);
        update_UI_balance();
    }
    else {
        set_up_account();
    }
}

void MainWindow::take_money() {
    take_money_button_->setEnabled(false);
    int money_taken = account_.get_balance();
    account_.withdraw_money(money_taken);

    QString text = "You withdraw " + QString::number(money_taken) + "$\n";
    text += "Your balance: 0$";
    textbox2_->setText(text);
}

void MainWindow::place_bet() {
    int max_bet = account_.get_balance();
    bool ok;
    bet_ = QInputDialog::getInt(nullptr, "Bet", "Place your bet", 1, 1, max_bet, 1, &ok);

    if(!ok) {
        place_bet();
    }
    else {
        account_.place_bet();
    }
}

void MainWindow::update_UI_balance() {
    int balance = account_.get_balance();
    QString text = "Your balance: " + QString::number(balance) + "$";

    if(account_.is_bet_placed()) {
        text += "\nYour bet: " + QString::number(bet_) + "$";
    }
    textbox2_->setText(text);
}

void MainWindow::new_round() {
    set_up_UI();
    if(account_.get_balance()==0) {
        set_up_account();
    }
    place_bet();
    game_.new_round();

    hit_button_->setEnabled(true);
    stay_button_->setEnabled(true);

    if(game_.is_blackjack_player()) {
        hit_button_->setEnabled(false);
        stay_button_->setEnabled(false);
        update_UI_cards(false);
    }
    else {
        update_UI_cards(true);
    }
    update_UI_game_status();
}

/*
void MainWindow::reset_game() {
    int result = QMessageBox::question(this, "Confirmation", "Do you want to"
    " reset the game? A new deck will be created, and your game history from"
    " this round will not be saved.", QMessageBox::Yes | QMessageBox::Cancel);

    if (result == QMessageBox::Yes) {
        take_money();
        game_.reset_game();
        account_.empty_account();
        set_up_UI();
    }
}
*/

void MainWindow::set_up_UI() {
    account_.empty_bet();
    update_UI_balance();

    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);
    take_money_button_->setEnabled(false);

    textbox1_->setText("Press the 'New round'-button to start the game");

    for(auto dealer_card_holder : dealer_card_holders_) {
        dealer_card_holder->setPixmap(QPixmap());
    }
    for(auto player_card_holder : player_card_holders_) {
        player_card_holder->setPixmap(QPixmap());
    }
}

void MainWindow::player_hit() {
    game_.player_hit();
    update_UI_cards(true);
    update_UI_game_status();

    if(game_.is_blackjack_player()) {
        dealer_turn();
    }
    else if(game_.is_player_over()) {
        hit_button_->setEnabled(false);
        stay_button_->setEnabled(false);
    }
}

void MainWindow::dealer_turn() {
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);

    game_.dealer_turn();
    update_UI_cards(false);
    update_UI_game_status();
}

void MainWindow::update_UI_cards(bool is_players_turn) {
    const std::vector<std::unique_ptr<Card>>& dealer_hand = game_.get_dealer_hand();
    const std::vector<std::unique_ptr<Card>>& player_hand = game_.get_player_hand();

    int i = 0;
    for (const auto& dealer_card : dealer_hand) {
        if(i>NUM_CARD_HOLDERS-1) {
            i=NUM_CARD_HOLDERS-1;
        }
        if(is_players_turn and i==1) {
            QString card_image_path = QString(":/cards/backside.png");
            QPixmap pixmap = load_pixmap_from_resource(card_image_path);
            dealer_card_holders_.at(i)->setPixmap(pixmap.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else {
            int suit_number = dealer_card->get_suit();
            int value_number = dealer_card->get_value();
            QString card_image_path = QString(":/cards/%1_%2.png").arg(value_number).arg(suit_number);
            QPixmap pixmap = load_pixmap_from_resource(card_image_path);
            dealer_card_holders_.at(i)->setPixmap(pixmap.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        i++;
    }

    i = 0;
    for (const auto& player_card : player_hand) {
        if(i>NUM_CARD_HOLDERS-1) {
            i=NUM_CARD_HOLDERS-1;
        }
        int suit_number = player_card->get_suit();
        int value_number = player_card->get_value();
        QString card_image_path = QString(":/cards/%1_%2.png").arg(value_number).arg(suit_number);
        QPixmap pixmap(card_image_path);
        player_card_holders_.at(i)->setPixmap(pixmap.scaled(player_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        i++;
    }
}

void MainWindow::update_UI_game_status() {
    int player_score = game_.get_player_points();
    int player_secondary_score = game_.get_player_secondary_points();
    int dealer_score = game_.get_dealer_points();

    if(game_.get_winner()=="Player") {
        QString text = "You won!\n";
        if(game_.is_blackjack_player()) {
            text += "You got blackjack!\n";
        }
        if(game_.is_dealer_over()) {
            text += "Dealer went bust!";
        }
        else if(!game_.is_blackjack_player() and !game_.is_dealer_over()){
            text += "Your score: " + QString::number(player_score) + "\n";
            text += "Dealer score: " + QString::number(dealer_score) + "\n";
        }
        textbox1_->setText(text);
        account_.add_balance(bet_);
        account_.empty_bet();
        m_db->add_win_record(1,true);
        if(account_.get_balance()>0) {
            take_money_button_->setEnabled(true);
        }
    }

    else if(game_.get_winner()=="Dealer") {
        QString text = "Dealer won! \n";
        if(game_.is_blackjack_player() and game_.is_blackjack_dealer()) {
            text += "You both got blackjack!\n";
        }
        else if(game_.is_blackjack_dealer() and !game_.is_player_over()) {
            text += "Dealer got blackjack!\n";
            text += "Your score: " + QString::number(player_score) + "\n";
        }
        else if(game_.is_player_over()) {
            text += "You went bust!";
        }
        else {
            text += "Your score: " + QString::number(player_score) + "\n";
            text += "Dealer score: " + QString::number(dealer_score) + "\n";
        }
        textbox1_->setText(text);
        account_.decrease_balance(bet_);
        account_.empty_bet();
        m_db->add_win_record(1,false);
        if(account_.get_balance()>0) {
            take_money_button_->setEnabled(true);
        }
    }

    else if(game_.get_winner()=="Tie") {
        QString text = "It's a tie!\nYou both got blackjack!";
        textbox1_->setText(text);
        account_.empty_bet();
        if(account_.get_balance()>0) {
            take_money_button_->setEnabled(true);
        }
    }

    else {
        QString text = "Your score: " + QString::number(player_score);
        if(player_secondary_score!=player_score) {
            text += " or " + QString::number(player_secondary_score);
        }
        text += "\n\nPress 'Hit' to draw new card\n";
        text += "Press 'Stay' to stay";
        textbox1_->setText(text);
    }
    update_UI_balance();
}

QPixmap MainWindow::load_pixmap_from_resource(const QString& file_path) {
    QPixmap pixmap;
    QFile file(file_path);
    if (!file.exists()) {
        qDebug() << "Image file not found: " << file_path;
        return pixmap; // Return an empty pixmap if the file doesn't exist
    }

    if (!pixmap.load(file_path)) {
        qDebug() << "Failed to load image from file: " << file_path;
        return pixmap; // Return an empty pixmap if the image couldn't be loaded
    }

    return pixmap;
}

void MainWindow::open_stats_window() {
    statistics_window_.show();
}

void MainWindow::play() {
    set_up_UI();
}



