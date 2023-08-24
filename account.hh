#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <database.hh>

class Account
{
public:
    /**
     * @brief Account constructor
     * @param Pointer to the database object
     */
    Account(Database *db);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief Set up the users account
     * @param Users chosen money deposit
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
    void add_balance();

    /**
     * @brief Decrease account balance
     */
    void decrease_balance();

    /**
     * @brief Withdraw money from the account
     */
    void withdraw_money();

    /**
     * @brief Empty the players account
     */
    void empty_account();

    /**
     * @brief Place the players bet
     * @param money - The bet user placed
     */
    void place_bet(int money);

    /**
     * @brief Take the players bet off
     */
    void empty_bet();

    /**
     * @brief Check if player has placed a bet
     * @return True or false
     */
    bool is_bet_placed();

    /**
     * @brief Get the bet that user has placed
     * @return The bet
     */
    int get_bet();

private:
    int balance_ = 0;
    int bet_;
    int money_deposited_;
    int money_won_;
    bool bet_placed_ = false;
    Database *m_db;
};

#endif // ACCOUNT_HH
