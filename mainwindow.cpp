#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Database *db, QWidget *parent) :
    QMainWindow(parent),
    m_db(db),
    ui(new Ui::MainWindow),
    account_(db),
    statistics_window_(db)
{
    // Set up fonts
    QFont button_font1("Tahoma", 16, QFont::DemiBold);
    QFont button_font2("Tahoma", 12, QFont::DemiBold);
    QFont button_font3("Tahoma", 10, QFont::DemiBold);
    QFont text_browser_font("Tahoma", 22);

    // Set up the main widget
    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Create the main layout for the central widget
    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);

    /*
    //DSDSADSAD
    QHBoxLayout* deck_layout = new QHBoxLayout;

    // Create a scroll area to contain the labels
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // Allow the scroll area to resize its widget
    QWidget* scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setFixedHeight(100);
    scrollWidget->setLayout(deck_layout); // Set the horizontal layout as the widget for scrolling

    // FDSKJDKFDSFKLDSFJSFLSDFLSKFLLDJ
    for (int i = 0; i <= game_.get_deck_size(); i++) {
        QLabel* deck_label = new QLabel(scrollWidget); // Create labels within the scroll widget
        if (i == 0) {
            deck_label->setText("Cards left");
            deck_label->setFont(button_font3);
            deck_label->setStyleSheet("color: white");
        } else {
            deck_label->setFixedSize(1, 50);
            deck_label->setStyleSheet("background-color: black");
        }
        deck_layout->addWidget(deck_label);
    }
    main_layout->addWidget(scrollArea);
    */

    // Create the dealers group of labels for the cards
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

    // Create the dealers group of labels for the cards
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

    // Create a horizontal layout for Hit, Stay and Withdraw buttons
    QHBoxLayout* upper_button_layout = new QHBoxLayout;

    // Create the buttons and add them to the upper button layout
    hit_button_ = new QPushButton("Hit", this);
    hit_button_->setObjectName("Hit");
    hit_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    hit_button_->setStyleSheet("background-color: green");
    hit_button_->setFont(button_font1);
    buttons_.append(hit_button_);

    stay_button_ = new QPushButton("Stay", this);
    stay_button_->setObjectName("Stay");
    stay_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    stay_button_->setStyleSheet("background-color: red");
    stay_button_->setFont(button_font1);
    buttons_.append(stay_button_);

    withdraw_money_button_ = new QPushButton("Withdraw money", this);
    withdraw_money_button_->setObjectName("Withdraw");
    withdraw_money_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    withdraw_money_button_->setStyleSheet("background-color: yellow");
    withdraw_money_button_->setFont(button_font3);
    buttons_.append(withdraw_money_button_);

    upper_button_layout->addWidget(hit_button_);
    upper_button_layout->addWidget(stay_button_);
    upper_button_layout->addWidget(withdraw_money_button_);
    upper_button_layout->addStretch(1);

    // Create a horizontal layout for New round and statistics buttons
    QHBoxLayout* lower_button_layout = new QHBoxLayout;

    // // Create the buttons and add them to the lower button layout
    new_round_button_ = new QPushButton("New round", this);
    new_round_button_->setObjectName("New round");
    new_round_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    new_round_button_->setStyleSheet("background-color: white");
    new_round_button_->setFont(button_font2);
    buttons_.append(new_round_button_);

    statistics_button_ = new QPushButton("Stats", this);
    statistics_button_->setObjectName("Stats");
    statistics_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    statistics_button_->setStyleSheet("background-color: white");
    statistics_button_->setFont(button_font2);
    buttons_.append(statistics_button_);

    lower_button_layout->addWidget(new_round_button_);
    //button_layout2->addWidget(reset_button_);
    lower_button_layout->addWidget(statistics_button_);
    lower_button_layout->addStretch(1);

    // Create a vertical layout for textboxes
    QVBoxLayout* text_box_layout = new QVBoxLayout;

    // Create the textboxes
    textbox1_ = new QTextBrowser();
    textbox1_->setStyleSheet("padding: 22px; color: white; border-style: dashed; border-width: 8px; border-color: white");
    textbox1_->setFont(text_browser_font);
    text_box_layout->addWidget(textbox1_);

    textbox2_ = new QTextBrowser();
    textbox2_->setStyleSheet("padding: 22px; color: white; border-style: dashed; border-width: 8px; border-color: white");
    textbox2_->setFont(text_browser_font);
    text_box_layout->addWidget(textbox2_);

    // Add the groups of card labels to the main layout
    main_layout->addLayout(dealer_layout);
    main_layout->addLayout(player_layout);

    // Wrap upper_button_layout and lower_button_layout in a QVBoxLayout
    QVBoxLayout* buttons_layouts_container = new QVBoxLayout;
    buttons_layouts_container->addLayout(upper_button_layout);
    buttons_layouts_container->addLayout(lower_button_layout);

    // Create a horizontal layout to hold the text_box_layout and button_layouts
    QHBoxLayout* right_layout = new QHBoxLayout;

    // Add the QVBoxLayout with button_layouts to the right_layout
    right_layout->addLayout(buttons_layouts_container);

    // Add the text_box_layout to the right_layout
    right_layout->addLayout(text_box_layout);

    // Add the right_layout to the main layout
    main_layout->addLayout(right_layout);

    // Set the main layout as the central widget's layout
    central_widget->setLayout(main_layout);
    central_widget->setStyleSheet("background-color: #008080");

    // Connect slots
    connect(hit_button_, &QPushButton::clicked, this, &MainWindow::on_hit_button_pressed);
    connect(stay_button_, &QPushButton::clicked, this, &MainWindow::dealer_turn);
    connect(new_round_button_, &QPushButton::clicked, this, &MainWindow::on_new_round_button_pressed);
    //connect(reset_button_, &QPushButton::clicked, this, &MainWindow::reset_game);
    connect(withdraw_money_button_, &QPushButton::clicked, this, &MainWindow::on_withdraw_button_pressed);
    connect(statistics_button_, &QPushButton::clicked, this, &MainWindow::on_statistics_button_pressed);

    // Initiate the game
    play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_up_account() {
    // Ask player for the sum they want to deposit to their account
    bool ok;
    int money = QInputDialog::getInt(nullptr, "Account", "Enter money to your account", 1, 10, 100, 1, &ok);

    // Ask again for the player to set the deposit, if they close the dialog
    if(!ok) {
        set_up_account();
    }
    else {
        account_.set_up_account(money);
        update_UI_balance();
    }
}

void MainWindow::on_withdraw_button_pressed() {
    // Withdraw players money, disable the withdraw button and update UI
    switch_button_enabled(false, {"Withdraw"});
    int money_taken = account_.get_balance();
    account_.withdraw_money(money_taken);
    statistics_window_.load_money_data();

    QString text = "You withdraw " + QString::number(money_taken) + "$\n";
    text += "Your balance: 0$";
    textbox2_->setText(text);
}

void MainWindow::place_bet() {
    // Ask player for their bet and place the bet
    int max_bet = account_.get_balance();
    bool ok;
    bet_ = QInputDialog::getInt(nullptr, "Bet", "Place your bet", 1, 1, max_bet, 1, &ok);

    // Ask again for the player to set the bet, if they close the dialog
    if(!ok) {
        place_bet();
    }
    else {
        account_.place_bet();
    }
}

void MainWindow::update_UI_balance() {
    // Update money related data shown on UI
    int balance = account_.get_balance();
    QString text = "Your balance: " + QString::number(balance) + "$";

    if(account_.is_bet_placed()) {
        text += "\nYour bet: " + QString::number(bet_) + "$";
    }
    textbox2_->setText(text);
}

void MainWindow::on_new_round_button_pressed() {
    // Set up the requirements for a new round of blackjack and initiate the round
    set_up_UI();
    if(account_.get_balance()==0) {
        set_up_account();
    }
    place_bet();
    game_.new_round();
    switch_button_enabled(true, {"Hit", "Stay"});
    switch_button_enabled(false, {"New round"});

    // If player gets blackjack on the initial draw, disable players buttons
    // and reveal dealers initial cards
    if(game_.is_blackjack_player()) {
        switch_button_enabled(false, {"Hit", "Stay"});
        update_UI_cards(false);
    }
    else {
        update_UI_cards(true);
    }
    update_UI_game_status();
}

void MainWindow::set_up_UI() {
    // Empty players bet, disable players buttons and update UI
    account_.empty_bet();
    update_UI_balance();
    switch_button_enabled(false, {"Hit", "Stay", "Withdraw"});
    textbox1_->setText("Press the 'New round'-button to start the game");

    // Set empty pixmaps to the card holders to clear the cards from screen
    for(auto dealer_card_holder : qAsConst(dealer_card_holders_)) {
        dealer_card_holder->setPixmap(QPixmap());
    }
    for(auto player_card_holder : qAsConst(player_card_holders_)) {
        player_card_holder->setPixmap(QPixmap());
    }
}

void MainWindow::on_hit_button_pressed() {
    // Draw card for player and update UI
    game_.player_hit();
    update_UI_cards(true);
    update_UI_game_status();

    // If player gets blackjack, initiate dealers turn and disable players buttons
    if(game_.is_blackjack_player()) {
        dealer_turn();
    }
    else if(game_.is_player_over()) {
        switch_button_enabled(false, {"Hit", "Stay"});
    }
}

void MainWindow::dealer_turn() {
    // Disable players buttons, initiate dealers turn and update UI
    switch_button_enabled(false, {"Hit", "Stay"});
    game_.dealer_turn();
    update_UI_cards(false);
    update_UI_game_status();
}

void MainWindow::update_UI_cards(bool is_players_turn) {
    const std::vector<std::unique_ptr<Card>>& dealer_hand = game_.get_dealer_hand();
    const std::vector<std::unique_ptr<Card>>& player_hand = game_.get_player_hand();

    // Display dealers cards
    int i = 0;
    for (const auto& dealer_card : dealer_hand) {
        // If number of cards exceeds number of cardholders, stack them on top of another
        if(i>NUM_CARD_HOLDERS-1) {
            i=NUM_CARD_HOLDERS-1;
        }
        // If players turn, don't show the dealers second card
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

    // Display players cards
    i = 0;
    for (const auto& player_card : player_hand) {
        // If number of cards exceeds number of cardholders, stack them on top of another
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

    // Update UI based on game status
    if(game_.get_winner()=="Player") {
        update_UI_player_won(player_score, dealer_score);
    }
    else if(game_.get_winner()=="Dealer") {
        update_UI_dealer_won(player_score, dealer_score);
    }
    else if(game_.get_winner()=="Tie") {
        update_UI_tie();
    }
    else {
        update_UI_ongoing(player_score, player_secondary_score);
    }

    // Update money related texts on screen
    update_UI_balance();

    // Update statistics window
    statistics_window_.load_money_data();
    statistics_window_.load_game_data();
}

void MainWindow::update_UI_ongoing(int player_score, int player_secondary_score) {
    // Display players and dealers score
    QString text = "Your score: " + QString::number(player_score);
    if(player_secondary_score!=player_score) {
        text += " or " + QString::number(player_secondary_score);
    }
    text += "\n\nPress 'Hit' to draw new card\n";
    text += "Press 'Stay' to stay";
    textbox1_->setText(text);
}

void MainWindow::update_UI_player_won(int player_score, int dealer_score) {
    // Display players winning message based on the way player won
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

    // Update account and database information
    account_.add_balance(bet_);
    account_.empty_bet();
    m_db->add_win_record(1,true);

    // Make withdraw possible only if money left
    if(account_.get_balance()>0) {
        switch_button_enabled(true, {"Withdraw"});
    }
    // Make it possible to start a new round of blackjack
    switch_button_enabled(true, {"New round"});
}

void MainWindow::update_UI_dealer_won(int player_score, int dealer_score) {
    // Display dealers winning message based on the way dealer won
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

    // Update account and database information
    account_.decrease_balance(bet_);
    account_.empty_bet();
    m_db->add_win_record(1,false);

    // Make withdraw possible only if money left
    if(account_.get_balance()>0) {
        switch_button_enabled(true, {"Withdraw"});
    }
    // Make it possible to start a new round of blackjack
    switch_button_enabled(true, {"New round"});
}

void MainWindow::update_UI_tie() {
    // Display tie message and take the bet of
    QString text = "It's a tie!\nYou both got blackjack!";
    textbox1_->setText(text);
    account_.empty_bet();

    // Make withdraw possible only if money left
    if(account_.get_balance()>0) {
        switch_button_enabled(true, {"Withdraw"});
    }
    // Make it possible to start a new round of blackjack
    switch_button_enabled(true, {"New round"});
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

void MainWindow::on_statistics_button_pressed() {
    statistics_window_.show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton result = QMessageBox::question(
        this,
        "Confirmation",
        "Are you sure you want to exit?\nYour current money left will be withdrawed.",
        QMessageBox::Yes | QMessageBox::No
    );

    if (result == QMessageBox::Yes) {
        // If user has money on the account, withdraw it upon exit
        if(account_.get_balance()>0) {
            int money_taken = account_.get_balance();
            account_.withdraw_money(money_taken);
        }
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::switch_button_enabled(bool enable, std::vector<std::string> button_names) {
    // Loop through the given button_names and buttons_
    // and enable or disable buttons which names match the button_name
    for (const std::string &button_name : button_names) {
        for (QPushButton *button : qAsConst(buttons_)) {
            if(QString::fromStdString(button_name) == button->objectName()) {
                button->setEnabled(enable);
            }
        }
    }
}

void MainWindow::play() {
    set_up_UI();
}



