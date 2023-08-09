#include "mainwindow.hh"
#include "ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    QFont button_font1("Tahoma", 16, QFont::DemiBold);
    QFont button_font2("Tahoma", 12, QFont::DemiBold);

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

    button_layout1->addWidget(hit_button_);
    button_layout1->addWidget(stay_button_);
    button_layout1->addStretch(1);
    QHBoxLayout* button_layout2 = new QHBoxLayout;

    new_round_button_ = new QPushButton("New round", this);
    new_round_button_->setObjectName("New round");
    new_round_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    new_round_button_->setStyleSheet("background-color: white");
    new_round_button_->setFont(button_font2);

    reset_button_ = new QPushButton("Reset game", this);
    reset_button_->setObjectName("Reset game");
    reset_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    reset_button_->setStyleSheet("background-color: white");
    reset_button_->setFont(button_font2);

    stat_button_ = new QPushButton("Stats", this);
    stat_button_->setObjectName("Stats");
    stat_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    stat_button_->setStyleSheet("background-color: white");
    stat_button_->setFont(button_font2);

    button_layout2->addWidget(new_round_button_);
    button_layout2->addWidget(reset_button_);
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
    connect(reset_button_, &QPushButton::clicked, this, &MainWindow::reset_game);

    play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_up_account() {
    account_.empty_account();
    bool ok;
    int money = QInputDialog::getInt(nullptr, "Account", "Enter money to your account", 1, 10, 100, 1, &ok);
    if(ok) {
        account_.insert_money(money);
        update_UI_balance();
    }
}

void MainWindow::place_bet() {
    int max_bet = account_.get_balance();
    if(max_bet>0) {
        bet_placed_ = true;
        bool ok;
        bet_ = QInputDialog::getInt(nullptr, "Bet", "Place your bet", 1, 1, max_bet, 1, &ok);
    }
    else {
        set_up_account();
    }
}

void MainWindow::update_UI_balance() {
    int balance = account_.get_balance();
    QString text = "Your balance: " + QString::number(balance) + "$";
    if(bet_placed_) {
        text += "\nYour bet: " + QString::number(bet_) + "$";
    }
    textbox2_->setText(text);
}

void MainWindow::new_round() {
    set_up_UI();
    place_bet();
    game_.new_round();
    hit_button_->setEnabled(true);
    stay_button_->setEnabled(true);

    if(game_.get_player_points()==BLACKJACK_THRESHOLD) {
        hit_button_->setEnabled(false);
        stay_button_->setEnabled(false);
        update_UI(false);
    }
    else {
        update_UI(true);
    }
}

void MainWindow::reset_game() {
    game_.reset_game();
    set_up_UI();
    set_up_account();
}

void MainWindow::set_up_UI() {
    bet_placed_ = false;
    update_UI_balance();
    player_over_ = false;
    dealer_over_ = false;
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);

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
    update_UI(true);
    if(game_.get_player_points()==BLACKJACK_THRESHOLD) {
        dealer_turn();
    }
    else if(game_.get_player_points()>BLACKJACK_THRESHOLD) {
        player_over_ = true;
        update_UI(true);
    }
}

void MainWindow::dealer_turn() {
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);
    game_.dealer_turn();
    if(game_.get_dealer_points()>BLACKJACK_THRESHOLD) {
        dealer_over_ = true;
    }
    update_UI(false);
}

void MainWindow::update_UI(bool first_round) {
    const std::vector<std::unique_ptr<Card>>& dealer_hand = game_.get_dealer_hand();
    const std::vector<std::unique_ptr<Card>>& player_hand = game_.get_player_hand();

    int i = 0;
    for (const auto& dealer_card : dealer_hand) {
        if(i>NUM_CARD_HOLDERS-1) {
            i=NUM_CARD_HOLDERS-1;
        }
        if(first_round==true and i==1) {
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

    int player_score = game_.get_player_points();
    int player_secondary_score = game_.get_player_secondary_points();
    int dealer_score = game_.get_dealer_points();

    if(player_over_==true) {
        QString text = "You went bust! \nDealer won!";
        textbox1_->setText(text);
        hit_button_->setEnabled(false);
        stay_button_->setEnabled(false);
        bet_placed_ = false;
    }

    else if(dealer_over_==true) {
        QString text = "Dealer went bust! \nYou won!";
        textbox1_->setText(text);
        account_.insert_money(bet_);
        bet_placed_ = false;
    }

    else if(game_.get_winner()=="Ongoing") {
        QString text = "Your score: " + QString::number(player_score);
        if(player_secondary_score!=player_score) {
            text += " or " + QString::number(player_secondary_score);
        }
        text += "\n\nPress 'Hit' to draw new card \n";
        text += "Press 'Stay' to stay";
        textbox1_->setText(text);
    }

    else if(game_.get_winner()=="Player"){
        QString text = "You won! \n";
        if(game_.get_player_points()==BLACKJACK_THRESHOLD) {
            text += "You got blackjack!";
        }
        else {
            text += "Your score: " + QString::number(player_score) + "\n";
            text += "Dealer score: " + QString::number(dealer_score) + "\n";
        }
        textbox1_->setText(text);
        account_.insert_money(bet_);
        bet_placed_ = false;
    }

    else if(game_.get_winner()=="Dealer") {
        QString text = "Dealer won! \n";
        if(game_.get_dealer_points()==BLACKJACK_THRESHOLD) {
            text += "Dealer got blackjack!";
        }
        else {
            text += "Your score: " + QString::number(player_score) + "\n";
            text += "Dealer score: " + QString::number(dealer_score) + "\n";
        }
        textbox1_->setText(text);
        account_.take_money(bet_);
        bet_placed_ = false;
    }

    else if(game_.get_winner()=="Tie") {
        QString text = "It's a tie! \n";
        text += "You both got blackjack!";
        textbox1_->setText(text);
        bet_placed_ = false;
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

void MainWindow::play() {
    set_up_UI();
    set_up_account();
}





