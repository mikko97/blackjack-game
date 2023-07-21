#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // Set up the main widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the main layout for the central widget
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create the first group of frames (5 frames at the middle and upper side of the screen)
    QHBoxLayout* group1Layout = new QHBoxLayout;
    for (int i = 0; i < 8; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(200, 300);
        label->setPixmap(QPixmap());

        group1Layout->addWidget(label);
        dealer_card_holders_.append(label);
    }

    // Create the second group of frames (5 frames at the middle and lower side of the screen)
    QHBoxLayout* group2Layout = new QHBoxLayout;
    for (int i = 0; i < 8; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(200, 300);
        label->setPixmap(QPixmap());

        group2Layout->addWidget(label);
        player_card_holders_.append(label);
    }

    // Create a horizontal layout for the buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    // Add buttons to the button layout
    hit_button_ = new QPushButton("Hit", this);
    hit_button_->setObjectName("Hit");
    stay_button_ = new QPushButton("Stay", this);
    stay_button_->setObjectName("Stay");
    new_round_button_ = new QPushButton("New round", this);
    new_round_button_->setObjectName("New round");
    reset_button_ = new QPushButton("Reset", this);
    reset_button_->setObjectName("Reset game");

    hit_button_->setFixedSize(200, 100);
    stay_button_->setFixedSize(200, 100);
    new_round_button_->setFixedSize(200, 100);
    reset_button_->setFixedSize(200, 100);

    buttonLayout->addWidget(hit_button_);
    buttonLayout->addWidget(stay_button_);
    buttonLayout->addWidget(new_round_button_);
    buttonLayout->addWidget(reset_button_);

    // Add the groups of frames to the main layout
    mainLayout->addLayout(group1Layout);
    mainLayout->addLayout(group2Layout);

    // Add the button layout to the main layout
    mainLayout->addLayout(buttonLayout);

    // Set the main layout as the central widget's layout
    centralWidget->setLayout(mainLayout);

    buttons_.append(hit_button_);
    buttons_.append(stay_button_);
    buttons_.append(new_round_button_);
    buttons_.append(reset_button_);

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
    update_UI();
}

void MainWindow::reset_game() {
    game_.reset_game();
    set_up_UI();
}

void MainWindow::player_hit() {
    game_.player_hit();
    update_UI();
    if(game_.get_player_points()>=21) {
        // Tähän häviöviesti
        hit_button_->setEnabled(false);
        stay_button_->setEnabled(false);
    }
}

void MainWindow::dealer_turn() {
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);
    game_.dealer_turn();
    update_UI();
}

void MainWindow::set_up_UI() {
    hit_button_->setEnabled(false);
    stay_button_->setEnabled(false);
    for(auto dealer_card_holder : dealer_card_holders_) {
        dealer_card_holder->setPixmap(QPixmap());
    }
    for(auto player_card_holder : player_card_holders_) {
        player_card_holder->setPixmap(QPixmap());
    }
}

void MainWindow::update_UI() {
    const std::vector<std::unique_ptr<Card>>& dealer_hand = game_.get_dealer_hand();
    const std::vector<std::unique_ptr<Card>>& player_hand = game_.get_player_hand();

    if (!dealer_hand.empty()) {
        int i = 0;
        for (const auto& dealer_card : dealer_hand) {
            int suit_number = dealer_card->get_suit();
            int value_number = dealer_card->get_value();
            QString card_image_path = QString(":/cards/%1_%2.png").arg(value_number).arg(suit_number);
            QPixmap pixmap(card_image_path);

            dealer_card_holders_.at(i)->setPixmap(pixmap.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            i++;
        }
    }

    if (!player_hand.empty()) {
        int i = 0;
        for (const auto& player_card : player_hand) {
            int suit_number = player_card->get_suit();
            int value_number = player_card->get_value();
            QString card_image_path = QString(":/cards/%1_%2.png").arg(value_number).arg(suit_number);
            QPixmap pixmap(card_image_path);

            player_card_holders_.at(i)->setPixmap(pixmap.scaled(player_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            i++;
        }
    }
}

void MainWindow::play() {
    set_up_UI();
}





