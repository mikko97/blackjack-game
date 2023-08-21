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

    // Create the dealers group of labels for the cards
    QString card_image_path = QString(":/cards/backside_5.png");
    deck_pixmap_ = load_pixmap_from_resource(card_image_path);
    QHBoxLayout* dealer_layout = new QHBoxLayout;
    for (int i = 0; i < NUM_CARD_HOLDERS; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(CARD_HOLDER_WIDTH, CARD_HOLDER_HEIGHT);
        label->setPixmap(QPixmap());
        label->setStyleSheet("background-color: transparent");
        dealer_layout->addWidget(label);

        // Create the deck
        if(i==NUM_CARD_HOLDERS - 1) {
            deck_holder_ = label;
            deck_holder_->setPixmap(deck_pixmap_.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
            shadow->setBlurRadius(50);
            shadow->setOffset(10);
            label->setGraphicsEffect(shadow);
        }
        // Create the group of labels for dealers playing cards
        else {
            dealer_card_holders_.append(label);
            dealer_card_positions_.append(label->pos());
        }
    }

    // Create the players group of labels for the cards
    QHBoxLayout* player_layout = new QHBoxLayout;
    for (int i = 0; i < NUM_CARD_HOLDERS; ++i)
    {
        QLabel* label = new QLabel(this);
        label->setFixedSize(CARD_HOLDER_WIDTH, CARD_HOLDER_HEIGHT);
        label->setPixmap(QPixmap());
        label->setStyleSheet("background-color: transparent");

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
    int money = QInputDialog::getInt(nullptr, "Account", ACCOUNT_DEPOSIT, 1, 10, 100, 1, &ok);

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
    bet_ = QInputDialog::getInt(nullptr, "Bet", PLACE_BET, 1, 1, max_bet, 1, &ok);

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
    are_player_cards_animated_.clear();
    are_player_cards_animated_.resize(NUM_CARD_HOLDERS, false);
    are_dealer_cards_animated_.clear();
    are_dealer_cards_animated_.resize(NUM_CARD_HOLDERS, false);

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
    textbox1_->setText(NEW_ROUND_INSTRUCTION);

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
    display_dealer_cards(is_players_turn);
    display_player_cards();
}

void MainWindow::animate_card(QLabel* card, const QPoint& endPos) {
    // Configure the animation
    QEventLoop loop;
    QPropertyAnimation* animation = new QPropertyAnimation(card, "pos");
    animation->setDuration(1000);
    animation->setStartValue(deck_holder_->pos());
    animation->setEndValue(endPos);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    // Ensure that function is not exited until the animation is over
    QObject::connect(animation, &QPropertyAnimation::finished, animation, [&loop]() {
        loop.quit();
    });

    // Start animation, crop the deck and disable buttons until animation is over
    animation->start();
    switch_button_enabled(false, {"Hit", "Stay"});
    crop_deck_image();
    loop.exec();
    switch_button_enabled(true, {"Hit", "Stay"});
}

void MainWindow::display_dealer_cards(bool is_players_turn) {
    const std::vector<std::unique_ptr<Card>>& dealer_hand = game_.get_dealer_hand();
    int i = 0;

    for (const auto& dealer_card : dealer_hand) {
        // If over 9 cards have been dealt, stack the remaining ones on top of
        // another, to avoid them going of screen
        if (i > NUM_CARD_HOLDERS - 2) {
            i = NUM_CARD_HOLDERS - 2;
        }

        // If it's the players turn, don't show dealers second card
        if (is_players_turn && i == 1) {
            QString card_image_path = QString(":/cards/backside_6.png");
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

        // Animate only the cards that have not been drawn
        if (!are_dealer_cards_animated_.at(i)) {
            animate_card(dealer_card_holders_.at(i), dealer_card_holders_.at(i)->pos());
            are_dealer_cards_animated_.at(i) = true;
        }
        i++;
    }
}

void MainWindow::display_player_cards() {
    const std::vector<std::unique_ptr<Card>>& player_hand = game_.get_player_hand();
    int i = 0;

    for (const auto& player_card : player_hand) {
        // If over 9 cards have been dealt, stack the remaining ones on top of
        // another, to avoid them going of screen
        if (i > NUM_CARD_HOLDERS - 2) {
            i = NUM_CARD_HOLDERS - 2;
        }
        int suit_number = player_card->get_suit();
        int value_number = player_card->get_value();
        QString card_image_path = QString(":/cards/%1_%2.png").arg(value_number).arg(suit_number);
        QPixmap pixmap(card_image_path);
        player_card_holders_.at(i)->setPixmap(pixmap.scaled(player_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Animate only the cards that have not been drawn
        if (!are_player_cards_animated_.at(i)) {
            animate_card(player_card_holders_.at(i), player_card_holders_.at(i)->pos());
            are_player_cards_animated_.at(i) = true;
        }
        i++;
    }
}

void MainWindow::update_UI_game_status() {
    const int player_score = game_.get_player_points();
    const int player_secondary_score = game_.get_player_secondary_points();
    const int dealer_score = game_.get_dealer_points();

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

    // Update money related statistics if all money is spent
    if(account_.get_balance()==0) {
        statistics_window_.load_money_data();
    }
}

void MainWindow::update_UI_ongoing(int player_score, int player_secondary_score) {
    // Display players and dealers score
    QString text = "Your score: " + QString::number(player_score);
    if(player_secondary_score!=player_score) {
        text += " or " + QString::number(player_secondary_score);
    }
    text += GAME_INSTRUCTION;
    textbox1_->setText(text);
}

void MainWindow::update_UI_player_won(int player_score, int dealer_score) {
    // Display players winning message based on the way player won
    QString text = PLAYER_WON;
    if(game_.is_blackjack_player()) {
        text += PLAYER_GOT_BLACKJACK;
    }
    if(game_.is_dealer_over()) {
        text += DEALER_WENT_BUST;
    }
    else if(!game_.is_blackjack_player() and !game_.is_dealer_over()){
        text += "Your score: " + QString::number(player_score) + "\n";
        text += "Dealer score: " + QString::number(dealer_score) + "\n";
    }
    textbox1_->setText(text);
    updates_after_round(false);
}

void MainWindow::update_UI_dealer_won(int player_score, int dealer_score) {
    // Display dealers winning message based on the way dealer won
    QString text = DEALER_WON;
    if(game_.is_blackjack_player() and game_.is_blackjack_dealer()) {
        text += BOTH_GOT_BLACKJACK;
    }
    else if(game_.is_blackjack_dealer() and !game_.is_player_over()) {
        text += DEALER_GOT_BLACKJACK;
        text += "Your score: " + QString::number(player_score) + "\n";
    }
    else if(game_.is_player_over()) {
        text += PLAYER_WENT_BUST;
    }
    else {
        text += "Your score: " + QString::number(player_score) + "\n";
        text += "Dealer score: " + QString::number(dealer_score) + "\n";
    }
    textbox1_->setText(text);
    updates_after_round(false);
}

void MainWindow::update_UI_tie() {
    // Display tie message and take the bet of
    textbox1_->setText(GAME_IS_TIE);
    account_.empty_bet();

    // Make withdraw possible only if money left
    if(account_.get_balance()>0) {
        switch_button_enabled(true, {"Withdraw"});
    }
    // Make it possible to start a new round of blackjack
    switch_button_enabled(true, {"New round"});
}

void MainWindow::updates_after_round(bool player_won) {
    // Update account, database and statistics information
    if(player_won) {
        account_.add_balance(bet_);
    }
    else {
        account_.decrease_balance(bet_);
    }

    account_.empty_bet();
    m_db->add_win_record(1,player_won);
    statistics_window_.load_game_data();

    // Make withdraw possible only if money left
    if(account_.get_balance()>0) {
        switch_button_enabled(true, {"Withdraw"});
    }
    // Make it possible to start a new round of blackjack
    switch_button_enabled(true, {"New round"});
}

void MainWindow::crop_deck_image() {
    cards_left_ -=1;
    if(cards_left_==0) {
        cards_left_ = 260;
    }

    // Define the initial height and the height to remove when only 1 card is left
    int initial_height = deck_pixmap_.height();
    int height_to_remove_for_last_card = 580;

    // Calculate the height to remove based on the number of cards remaining
    int height_to_remove = height_to_remove_for_last_card * (260 - cards_left_) / 259;

    // Calculate the new height of the cropped image
    int new_height = initial_height - height_to_remove;

    // Create a new QPixmap for the cropped image
    QPixmap cropped_pixmap = deck_pixmap_.copy(0, 0, deck_pixmap_.width(), new_height);

    // Set the new pixmap
    deck_holder_->setPixmap(cropped_pixmap.scaled(dealer_card_holders_.at(0)->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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



