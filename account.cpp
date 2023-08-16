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
}

void Account::withdraw_money(int money) {
    empty_account();
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
