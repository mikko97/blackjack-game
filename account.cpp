#include "account.hh"

Account::Account(Database *db): m_db(db)
{

}

Account::~Account()
{
}

void Account::set_up_account(int money) {
    empty_account();
    add_balance(money);

    // Save the money deposited as a negative value for later use
    first_data_point_ = -money;
}

int Account::get_balance() {
    return balance_;
}

void Account::add_balance(int money) {
    balance_ = balance_ + money;
}

void Account::decrease_balance(int money) {
    balance_ = balance_ - money;

    // If player has used all their deposited money,
    // save that as a loss in the database
    if(balance_==0) {
        money_won_ = first_data_point_; // The negative value of the deposited money
        m_db->add_money_record(1, money_won_);
    }
}

void Account::withdraw_money(int money) {
    empty_account();

    // Add the negative value of the deposit to the money that was withdrawed
    // to get the amount of money that the user gained
    second_data_point_ = money;
    money_won_ = second_data_point_ + first_data_point_;
    m_db->add_money_record(1, money_won_);
}

void Account::empty_account() {
    balance_ = 0;
}

void Account::place_bet() {
    bet_placed_ = true;
}

void Account::empty_bet() {
    bet_placed_ = false;
}

bool Account::is_bet_placed() {
    return bet_placed_;
}
