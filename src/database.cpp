#include "headers/database.hh"

Database::Database(QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("blackjack.db");
}

Database::~Database() {
    m_db.close();
}

bool Database::open_database() {
    if (!m_db.open()) {
        db_opened_succesfully_ = false;
        return false;
    }
    db_opened_succesfully_ = true;
    return true;
}

bool Database::create_tables() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    QSqlQuery query;

    QString create_table_query = "CREATE TABLE IF NOT EXISTS win_record ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "user_id INTEGER,"
                              "round_won BOOL,"
                              "date_time DATETIME DEFAULT CURRENT_TIMESTAMP);";

    QString create_table_query2 = "CREATE TABLE IF NOT EXISTS money_record ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "user_id INTEGER,"
                              "money_won INTEGER,"
                              "date_time DATETIME DEFAULT CURRENT_TIMESTAMP);";

    if (!query.exec(create_table_query) or !query.exec(create_table_query2)) {
        return false;
    }
    return true;
}

bool Database::add_win_record(int user_id, bool round_won) {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    QSqlQuery query;

    query.prepare("INSERT INTO win_record (user_id, round_won) VALUES "
                  "(:user_id, :round_won)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":round_won", round_won);

    if (!query.exec()) {
        throw std::runtime_error("Error updating game record to database."
                                 "Do you want to ignore these messages in the future.");
    }
    return true;
}

bool Database::add_money_record(int user_id, int money_won) {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    QSqlQuery query;

    query.prepare("INSERT INTO money_record (user_id, money_won) VALUES "
                  "(:user_id, :money_won)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":money_won", money_won);

    if (!query.exec()) {
        throw std::runtime_error("Error updating game record to database."
                                 "Do you want to ignore these messages in the future.");
    }
    return true;
}

int Database::fetch_total_money_all_time() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    int total_money = 0;

    QSqlQuery query;
    query.prepare("SELECT SUM(money_won) AS total_money FROM money_record");

    if (!query.exec()) {
        throw std::runtime_error("Error fetching money data");
    }
    if (query.next()) {
        total_money = query.value("total_money").toInt();
    }
    return total_money;
}

QMap<std::string, int> Database::fetch_money_won_last_week() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    QMap<std::string, int> money_per_day;

    // Calculate the date 7 days ago from the current date
    QDateTime seven_days_ago = QDateTime::currentDateTime().addDays(-7);

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, SUM(money_won) AS money_won "
                  "FROM money_record "
                  "WHERE date_time >= :seven_days_ago "
                  "GROUP BY day");
    query.bindValue(":seven_days_ago", seven_days_ago);

    if (!query.exec()) {
        throw std::runtime_error("Error fetching money data");
    }
    while (query.next()) {
        QDateTime date_time = query.value("day").toDateTime();
        std::string date_time_string = date_time.toString("yyyy-MM-dd").toStdString();
        int money_won = query.value("money_won").toInt();
        money_per_day.insert(date_time_string, money_won);
    }

    // Populate map with zeros, if no data from a day
    for (int i = 7; i >= 0; i--) {
        std::string day = QDateTime::currentDateTime().addDays(-i).toString("yyyy-MM-dd").toStdString();
        if (!money_per_day.keys().contains(day)) {
            money_per_day.insert(day, 0);
        }
    }

    return money_per_day;
}

QMap<std::string, int> Database::fetch_wins_last_week() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    QMap<std::string, int> wins;

    // Calculate the date 7 days ago from the current date
    QDateTime seven_days_ago = QDateTime::currentDateTime().addDays(-7);

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, COUNT(*) AS rounds_won "
                  "FROM win_record "
                  "WHERE round_won = 1 AND date_time >= :seven_days_ago "
                  "GROUP BY day");
    query.bindValue(":seven_days_ago", seven_days_ago);

    if (!query.exec()) {
        throw std::runtime_error("Error fetching game data");
    }
    while (query.next()) {
        QDateTime date_time = query.value("day").toDateTime();
        std::string date_time_string = date_time.toString("yyyy-MM-dd").toStdString();
        int rounds_won = query.value("rounds_won").toInt();
        wins.insert(date_time_string, rounds_won);
    }

    // Populate map with zeros, if no data from a day
    for (int i = 7; i >= 0; i--) {
        std::string day = QDateTime::currentDateTime().addDays(-i).toString("yyyy-MM-dd").toStdString();
        if (!wins.keys().contains(day)) {
            wins.insert(day, 0);
        }
    }

    return wins;
}

#include <iostream>
QMap<std::string, int> Database::fetch_losses_last_week() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    //QMap<QDateTime, int> losses;
    QMap<std::string, int> losses;

    // Calculate the date 7 days ago from the current date
    QDateTime seven_days_ago = QDateTime::currentDateTime().addDays(-7);

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, COUNT(*) AS rounds_lost "
                  "FROM win_record "
                  "WHERE round_won = 0 AND date_time >= :seven_days_ago "
                  "GROUP BY day");
    query.bindValue(":seven_days_ago", seven_days_ago);

    if (!query.exec()) {
        throw std::runtime_error("Error fetching game");
    }
    while (query.next()) {
        QDateTime date_time = query.value("day").toDateTime();
        std::string date_time_string = date_time.toString("yyyy-MM-dd").toStdString();
        int rounds_lost = query.value("rounds_lost").toInt();
        losses.insert(date_time_string, rounds_lost);
    }

    // Populate map with zeros, if no data from a day
    for (int i = 7; i >= 0; i--) {
        std::string day = QDateTime::currentDateTime().addDays(-i).toString("yyyy-MM-dd").toStdString();
        if (!losses.keys().contains(day)) {
            losses.insert(day, 0);
        }
    }

    return losses;
}

int Database::fetch_total_wins_all_time() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    int total_wins = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS total_wins FROM win_record"
                  " WHERE round_won = 1");

    if (!query.exec() or !query.next()) {
        throw std::runtime_error("Error fetching game data");
    }
    else {
        total_wins = query.value("total_wins").toInt();
    }
    return total_wins;
}

int Database::fetch_total_losses_all_time() {
    if(!db_opened_succesfully_) {
        throw std::runtime_error("Database is not open.");
    }

    int total_losses = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS total_losses FROM win_record "
                  "WHERE round_won = 0");

    if (!query.exec() or !query.next()) {
        throw std::runtime_error("Error fetching game data");
    }
    else {
        total_losses = query.value("total_losses").toInt();
    }
    return total_losses;
}
