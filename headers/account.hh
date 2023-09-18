#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "database.hh"

class MainWindow;

class Account
{
public:
    /**
     * @brief Account constructor
     * @param Pointer to the database object
     */
    Account(Database *db, MainWindow& mainWindow);

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
    int get_balance() const;

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
    bool is_bet_placed() const;

    /**
     * @brief Get the bet that user has placed
     * @return The bet
     */
    int get_bet() const;

private:
    Database *m_db;
    MainWindow& main_window;

    int balance_ = 0;
    int bet_ = 0;
    int money_deposited_ = 0;
    int money_won_ = 0;
    bool bet_placed_ = false;
};

#endif // ACCOUNT_HH
