#ifndef ACCOUNT_HH
#define ACCOUNT_HH


class Account
{
public:
    /**
     * @brief Account constructor
     */
    Account();

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief Get balance of the account
     */
    int get_balance();

    /**
     * @brief Insert money to the account
     */
    void insert_money(int money);

    /**
     * @brief Take money from the account
     */
    void take_money(int money);

    /**
     * @brief Empty the account
     */
    void empty_account();

private:
    int balance_ = 0;
    int bet_;
};

#endif // ACCOUNT_HH
