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
     * @brief Fetch the money records of the user
     * @param int user_id
     * @return Vector containing the data
     */
    QVector<QPointF> fetch_money_records(int user_id);

    /**
     * @brief Fetch the winning records of the user
     * @param int user_id
     * @return Vector containing the data
     */
    QVector<QPointF> fetch_win_records(int user_id);

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
     * @brief Fetch total money won per day
     * @return Qmap, which has the day as key and the total money won as value
     */
    QMap<QDateTime, int> fetch_total_money_per_day();

    /**
     * @brief Fetch total games won per day
     * @return Qmap, which has the day as key and the total rounds won as value
     */
    QMap<QDateTime, int> fetch_total_wins_per_day();

    /**
     * @brief Fetch total games lost per day
     * @return Qmap, which has the day as key and the total rounds lost as value
     */
    QMap<QDateTime, int> fetch_total_losses_per_day();

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_HH
