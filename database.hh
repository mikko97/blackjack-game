#ifndef DATABASE_HH
#define DATABASE_HH

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QPointF>

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
    QMap<QDate, int> fetch_total_money_per_day();



    bool insert_initial_record(int user_id);
    bool check_initial_record_exists(int user_id);
    bool update_rounds_won(int user_id, int rounds_won);
    bool update_rounds_lost(int user_id, int rounds_lost);
    bool update_money_balance(int user_id, int money);
    QVector<QVariantMap> get_records();

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_HH
