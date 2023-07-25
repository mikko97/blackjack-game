#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // Set up the main widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the main layout for the central widget
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create the first group of frames (15 frames at the middle and upper side of the screen)
    QHBoxLayout* group1Layout = new QHBoxLayout;
    for (int i = 0; i < 15; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(200, 300);
        label->setPixmap(QPixmap());

        group1Layout->addWidget(label);
        dealer_card_holders_.append(label);
    }

    // Create the second group of frames (15 frames at the middle and lower side of the screen)
    QHBoxLayout* group2Layout = new QHBoxLayout;
    for (int i = 0; i < 15; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(200, 300);
        label->setPixmap(QPixmap());

        group2Layout->addWidget(label);
        player_card_holders_.append(label);
    }

    // Create a horizontal layout for the buttons
    QHBoxLayout* button_layout1 = new QHBoxLayout;

    // Add buttons to the button layout
    hit_button_ = new QPushButton("Hit", this);
    hit_button_->setObjectName("Hit");
    hit_button_->setFixedSize(200, 100);
    stay_button_ = new QPushButton("Stay", this);
    stay_button_->setObjectName("Stay");
    stay_button_->setFixedSize(200, 100);

    button_layout1->addWidget(hit_button_);
    button_layout1->addWidget(stay_button_);
    button_layout1->addStretch(1);

    QHBoxLayout* button_layout2 = new QHBoxLayout;
    new_round_button_ = new QPushButton("New round", this);
    new_round_button_->setObjectName("New round");
    new_round_button_->setFixedSize(200, 100);
    reset_button_ = new QPushButton("Reset game", this);
    reset_button_->setObjectName("Reset game");
    reset_button_->setFixedSize(200, 100);

    button_layout2->addWidget(new_round_button_);
    button_layout2->addWidget(reset_button_);
    button_layout2->addStretch(1);

    // Create a vertical layout
    QVBoxLayout* new_layout = new QVBoxLayout;
    //QLabel* textbox1 = new Q("New Label", this);
    textbox1_ = new QTextBrowser();
    new_layout->addWidget(textbox1_);

    // Add the groups of frames to the main layout
    mainLayout->addLayout(group1Layout);
    mainLayout->addLayout(group2Layout);

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
    mainLayout->addLayout(right_layout);

    // Set the main layout as the central widget's layout
    centralWidget->setLayout(mainLayout);

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


void MainWindow::new_round() {
    set_up_UI();
    game_.new_round();
    hit_button_->setEnabled(true);
    stay_button_->setEnabled(true);

    if(game_.get_player_points()==21) {
        update_UI(false);
        dealer_turn();
    }
    else {
        update_UI(true);
    }
}

void MainWindow::reset_game() {
    game_.reset_game();
    set_up_UI();
}

void MainWindow::player_hit() {
    game_.player_hit();
    update_UI(true);
    if(game_.get_player_points()==21) {
        dealer_turn();
    }
    else if(game_.get_player_points()>21) {
        player_over_ = true;
        update_UI(true);
    }
}

void MainWindow::dealer_turn() {
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);
    game_.dealer_turn();
    if(game_.get_dealer_points()>21) {
        dealer_over_ = true;
    }
    update_UI(false);
}

void MainWindow::set_up_UI() {
    player_over_ = false;
    dealer_over_ = false;
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);
    textbox1_->setText("Press the 'New round'-button to start the game");
    QFont font("Arial", 22, QFont::Normal);
    textbox1_->setFont(font);
    for(auto dealer_card_holder : dealer_card_holders_) {
        dealer_card_holder->setPixmap(QPixmap());
    }
    for(auto player_card_holder : player_card_holders_) {
        player_card_holder->setPixmap(QPixmap());
    }
}

void MainWindow::update_UI(bool first_round) {
    const std::vector<std::unique_ptr<Card>>& dealer_hand = game_.get_dealer_hand();
    const std::vector<std::unique_ptr<Card>>& player_hand = game_.get_player_hand();


    int i = 0;
    for (const auto& dealer_card : dealer_hand) {
        if(first_round==true and i==1) {
            QString card_image_path = QString(":/cards/backside");
            QPixmap pixmap(card_image_path);
            dealer_card_holders_.at(i)->setPixmap(pixmap.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else {
            int suit_number = dealer_card->get_suit();
            int value_number = dealer_card->get_value();
            QString card_image_path = QString(":/cards/%1_%2.png").arg(value_number).arg(suit_number);
            QPixmap pixmap(card_image_path);
            dealer_card_holders_.at(i)->setPixmap(pixmap.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        i++;
    }


    i = 0;
    for (const auto& player_card : player_hand) {
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
    }

    else if(dealer_over_==true) {
        QString text = "Dealer went bust! \nYou won!";
        textbox1_->setText(text);
    }

    else if(game_.get_winner()=="Ongoing") {
        QString text = "Your score: " + QString::number(player_score);
        if(player_secondary_score!=player_score) {
            text += " or " + QString::number(player_secondary_score);
        }
        text += "\nPress 'Hit' to draw new card. \n";
        text += "Press 'Stay' to stay";
        textbox1_->setText(text);
    }

    else if(game_.get_winner()=="Player"){
        QString text = "You won! \n";
        text += "Your score: " + QString::number(player_score) + "\n";
        text += "Dealer score: " + QString::number(dealer_score) + "\n";
        textbox1_->setText(text);
    }
    else if(game_.get_winner()=="Dealer") {
        QString text = "Dealer won! \n";
        text += "Your score: " + QString::number(player_score) + "\n";
        text += "Dealer score: " + QString::number(dealer_score) + "\n";
        textbox1_->setText(text);
    }
}

void MainWindow::play() {
    set_up_UI();
}





