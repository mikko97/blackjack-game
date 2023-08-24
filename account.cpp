#include "account.hh"

Account::Account(Database *db): m_db(db)
{

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

int Account::get_balance() {
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
        m_db->add_money_record(1, money_won_);
    }
}

void Account::withdraw_money() {
    // Add the negative value of the deposit to the money that was withdrawed
    // to get the amount of money that the user gained
    int money_withdrawed = get_balance();
    money_won_ = money_withdrawed + money_deposited_;
    m_db->add_money_record(1, money_won_);
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

bool Account::is_bet_placed() {
    return bet_placed_;
}

int Account::get_bet() {
    return bet_;
}



