#ifndef DATABASE_HH
#define DATABASE_HH

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QPointF>
#include <QDebug>


class Database : public QObject {
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    /**
     * @brief Open the database
     * @return Bool value if the opening was a success
     */
    bool open_database();

    /**
     * @brief Close database
     */
    void close_database();

    /**
     * @brief Create the database tables
     * @return Bool value if the creation was a success
     */
    bool create_tables();

    /**
     * @brief Fetch the winning records of the user
     * @param int user_id
     * @param bool round_won
     * @return Bool value if the adding of the record was a success
     */
    bool add_win_record(int user_id, bool round_won);

    /**
     * @brief Fetch the winning records of the user
     * @param int user_id
     * @param int money_won
     * @return Bool value if the adding of the record was a success
     */
    bool add_money_record(int user_id, int money_won);

    /**
     * @brief Fetch total games won per day
     * @return Qmap, which has the day as key and the total rounds won as value
     */
    //QMap<QDateTime, int> fetch_total_wins_per_day();

    /**
     * @brief Fetch total games lost per day
     * @return Qmap, which has the day as key and the total rounds lost as value
     */
    //QMap<QDateTime, int> fetch_total_losses_per_day();

    /**
     * @brief Fetch money won last week
     * @return Qmap, which has the day as key and the money won as value
     */
    QMap<QDateTime, int> fetch_money_won_last_week();

    /**
     * @brief Fetch total money won all time
     * @return The amount of money won
     */
    int fetch_total_money_all_time();

    /**
     * @brief Fetch total wins last week
     * @return Qmap, which has the day as key and the rounds won as value
     */
    QMap<QDateTime, int> fetch_wins_last_week();

    /**
     * @brief Fetch total losses last week
     * @return Qmap, which has the day as key and the rounds lost as value
     */
    QMap<QDateTime, int> fetch_losses_last_week();

    /**
     * @brief Fetch total rounds won all time
     * @return The amount of rounds won
     */
    int fetch_total_wins_all_time();

    /**
     * @brief Fetch total rounds lost all time
     * @return The amount of rounds lost
     */
    int fetch_total_losses_all_time();

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_HH
