#include "account.hh"

Account::Account()
{

}

Account::~Account()
{
}

int Account::get_balance() {
    return balance_;
}

void Account::insert_money(int money) {
    balance_ = balance_ + money;
}

void Account::take_money(int money) {
    balance_ = balance_ - money;
}

void Account::empty_account() {
    balance_ = 0;
}
