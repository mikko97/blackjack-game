#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <database.hh>

class Account
{
public:
    /**
     * @brief Account constructor
     */
    Account(Database *db);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief Set up the users account
     */
    void set_up_account(int money);

    /**
     * @brief Get balance of the account
     * @return The balance
     */
    int get_balance();

    /**
     * @brief Add account balance
     */
    void add_balance(int money);

    /**
     * @brief Decrease account balance
     */
    void decrease_balance(int money);

    /**
     * @brief Withdraw money from the account
     */
    void withdraw_money(int money);

    /**
     * @brief Empty the account
     */
    void empty_account();

    /**
     * @brief Place the players bet
     */
    void place_bet();

    /**
     * @brief Take the players bet off
     */
    void empty_bet();

    /**
     * @brief Place the players bet
     * @return bool value
     */
    bool is_bet_placed();

private:
    int balance_ = 0;
    int bet_;
    bool bet_placed_ = false;
    Database *m_db;
};

#endif // ACCOUNT_HH
