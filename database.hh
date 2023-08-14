#ifndef DATABASE_HH
#define DATABASE_HH

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class Database : public QObject {
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool open_database();
    void close_database();
    bool create_tables();
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
