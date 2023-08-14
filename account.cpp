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
    m_db->update_money_balance(1, -money);

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
    m_db->update_money_balance(1, money);
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
