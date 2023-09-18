#include "headers/mainwindow.hh"
#include "headers/account.hh"

Account::Account(Database *db, MainWindow& mainWindow):
    m_db(db), main_window(mainWindow)
{
    QObject::connect(&main_window, SIGNAL(db_error_occurred(QString)), &main_window,
                     SLOT(display_db_add_error_dialogue(QString)));
}

Account::~Account()
{
}

void Account::set_up_account(int money) {
    empty_account();
    balance_ = balance_ + money;

    // Save the money deposited as a negative value for later use
    money_deposited_ = -money;
}

int Account::get_balance() const{
    return balance_;
}

void Account::add_balance() {
    balance_ = balance_ + bet_;
}

void Account::decrease_balance() {
    balance_ = balance_ - bet_;

    // If player has used all their deposited money,
    // save that as a loss in the database
    if(balance_==0) {
        money_won_ = money_deposited_; // The negative value of the deposited money

        try {
            m_db->add_money_record(1, money_won_);
        }
        catch (const std::exception& e) {
            emit main_window.db_error_occurred(e.what());
        }
    }
}

void Account::withdraw_money() {
    // Add the negative value of the deposit to the money that was withdrawed
    // to get the amount of money that the user gained
    int money_withdrawed = get_balance();
    money_won_ = money_withdrawed + money_deposited_;

    try {
        m_db->add_money_record(1, money_won_);
    }
    catch (const std::exception& e) {
        emit main_window.db_error_occurred(e.what());
    }
    empty_account();
}

void Account::empty_account() {
    balance_ = 0;
}

void Account::place_bet(int money) {
    bet_ = money;
    bet_placed_ = true;
}

void Account::empty_bet() {
    bet_ = 0;
    bet_placed_ = false;
}

bool Account::is_bet_placed() const {
    return bet_placed_;
}

int Account::get_bet() const {
    return bet_;
}



