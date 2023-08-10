#include "database.hh"
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("blackjack_records.db");
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

    // Create the blackjack_records table if it doesn't exist
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS blackjack_records ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "user_id INTEGER,"
                              "rounds_won INTEGER,"
                              "rounds_lost INTEGER,"
                              "money_won INTEGER,"
                              "money_lost INTEGER);";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Error creating table: " << query.lastError();
        return false;
    }
    qDebug() << "Table created successfully!";
    return true;
}

bool Database::insert_initial_record(int user_id) {
    QSqlQuery query;

    QString insertQuery = "INSERT INTO blackjack_records (user_id, rounds_won, rounds_lost, money_won, money_lost) "
                          "VALUES (:user_id, 0, 0, 0, 0);";

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
    query.prepare("SELECT id FROM blackjack_records WHERE user_id = :user_id;");
    query.bindValue(":user_id", user_id);

    if (query.exec() && query.next()) {
        // Found a record for the user
        return true;
    } else {
        // No record found
        return false;
    }
}

bool Database::update_rounds_won(int user_id, int rounds_won) {
    QSqlQuery query;

    QString updateQuery = "UPDATE blackjack_records "
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

    QString updateQuery = "UPDATE blackjack_records "
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

bool Database::update_money_won(int user_id, int money_won) {
    QSqlQuery query;

    QString updateQuery = "UPDATE blackjack_records "
                          "SET money_won = money_won + :money_won "
                          "WHERE user_id = :user_id;";

    query.prepare(updateQuery);
    query.bindValue(":money_won", money_won);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error updating money won: " << query.lastError();
        return false;
    }
    qDebug() << "Money won updated successfully!";
    return true;
}

bool Database::update_money_lost(int user_id, int money_lost) {
    QSqlQuery query;

    QString updateQuery = "UPDATE blackjack_records "
                          "SET money_lost = money_lost + :money_lost "
                          "WHERE user_id = :user_id;";

    query.prepare(updateQuery);
    query.bindValue(":money_lost", money_lost);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error updating money lost: " << query.lastError();
        return false;
    }
    qDebug() << "Money lost updated successfully!";
    return true;
}

QVector<QVariantMap> Database::get_records() {
    QVector<QVariantMap> records;

    QSqlQuery query("SELECT * FROM blackjack_records;");
    if (query.exec()) {
        while (query.next()) {
            QVariantMap record;
            record["id"] = query.value("id").toInt();
            record["user_id"] = query.value("user_id").toInt();
            record["rounds_won"] = query.value("rounds_won").toInt();
            record["rounds_lost"] = query.value("rounds_lost").toInt();
            record["money_won"] = query.value("money_won").toInt();
            record["money_lost"] = query.value("money_lost").toInt();
            records.append(record);
        }
    } else {
        qDebug() << "Error fetching records: " << query.lastError();
    }

    return records;
}
