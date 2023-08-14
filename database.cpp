#include "database.hh"
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("blackjack_record.db");
}

Database::~Database() {
    close_database();
}

bool Database::open_database() {
    if (!m_db.open()) {
        qDebug() << "Error opening database: " << m_db.lastError();
        return false;
    }
    qDebug() << "Database opened successfully!";
    return true;
}

void Database::close_database() {
    m_db.close();
    qDebug() << "Database closed.";
}

bool Database::create_tables() {
    QSqlQuery query;

    // Create the blackjack_record table if it doesn't exist
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS blackjack_record ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "user_id INTEGER,"
                              "rounds_won INTEGER,"
                              "rounds_lost INTEGER,"
                              "money_balance INTEGER);";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Error creating table: " << query.lastError();
        return false;
    }
    qDebug() << "Table created successfully!";
    return true;
}

bool Database::insert_initial_record(int user_id) {
    QSqlQuery query;

    QString insertQuery = "INSERT INTO blackjack_record (user_id, rounds_won, rounds_lost, money_balance) "
                          "VALUES (:user_id, 0, 0, 0);";

    query.prepare(insertQuery);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error inserting initial record: " << query.lastError();
        return false;
    }
    qDebug() << "Initial record inserted successfully!";
    return true;
}

bool Database::check_initial_record_exists(int user_id) {
    QSqlQuery query;
    query.prepare("SELECT id FROM blackjack_record WHERE user_id = :user_id;");
    query.bindValue(":user_id", user_id);

    if (query.exec() && query.next()) {
        return true;
    } else {
        return false;
    }
}

bool Database::update_rounds_won(int user_id, int rounds_won) {
    QSqlQuery query;

    QString updateQuery = "UPDATE blackjack_record "
                          "SET rounds_won = rounds_won + :rounds_won "
                          "WHERE user_id = :user_id;";

    query.prepare(updateQuery);
    query.bindValue(":rounds_won", rounds_won);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error updating rounds won: " << query.lastError();
        return false;
    }
    qDebug() << "Rounds won updated successfully!";
    return true;
}

bool Database::update_rounds_lost(int user_id, int rounds_lost) {
    QSqlQuery query;

    QString updateQuery = "UPDATE blackjack_record "
                          "SET rounds_lost = rounds_lost + :rounds_lost "
                          "WHERE user_id = :user_id;";

    query.prepare(updateQuery);
    query.bindValue(":rounds_lost", rounds_lost);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error updating rounds lost: " << query.lastError();
        return false;
    }
    qDebug() << "Rounds lost updated successfully!";
    return true;
}

bool Database::update_money_balance(int user_id, int money) {
    QSqlQuery query;

    QString updateQuery = "UPDATE blackjack_record "
                          "SET money_balance = money_balance + :money_balance "
                          "WHERE user_id = :user_id;";

    query.prepare(updateQuery);
    query.bindValue(":money_balance", money);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error updating money balance: " << query.lastError();
        return false;
    }
    qDebug() << "Money balance updated successfully!";
    return true;
}

QVector<QVariantMap> Database::get_records() {
    QVector<QVariantMap> records;

    QSqlQuery query("SELECT * FROM blackjack_record;");
    if (query.exec()) {
        while (query.next()) {
            QVariantMap record;
            record["id"] = query.value("id").toInt();
            record["user_id"] = query.value("user_id").toInt();
            record["rounds_won"] = query.value("rounds_won").toInt();
            record["rounds_lost"] = query.value("rounds_lost").toInt();
            record["money_balance"] = query.value("money_balance").toInt();
            records.append(record);
        }
    } else {
        qDebug() << "Error fetching records: " << query.lastError();
    }

    return records;
}
