#include "database.hh"

Database::Database(QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("blackjack.db");
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
        qDebug() << "Error creating table: " << query.lastError();
        return false;
    }
    qDebug() << "Table created successfully!";
    return true;
}

bool Database::add_win_record(int user_id, bool round_won) {
    QSqlQuery query;

    query.prepare("INSERT INTO win_record (user_id, round_won) VALUES (:user_id, :round_won)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":round_won", round_won);

    if (!query.exec()) {
        qDebug() << "Error adding win record: " << query.lastError();
        return false;
    }

    qDebug() << "Win record added successfully!";
    return true;
}

bool Database::add_money_record(int user_id, int money_won) {
    QSqlQuery query;

    query.prepare("INSERT INTO money_record (user_id, money_won) VALUES (:user_id, :money_won)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":money_won", money_won);

    if (!query.exec()) {
        qDebug() << "Error adding money record: " << query.lastError();
        return false;
    }

    qDebug() << "Money record added successfully!";
    return true;
}

int Database::fetch_total_money_all_time() {
    int total_money = 0;

    QSqlQuery query;
    query.prepare("SELECT SUM(money_won) AS total_money FROM money_record");

    if (!query.exec()) {
        qDebug() << "Error fetching total money all time: " << query.lastError();
        return total_money; // Return 0 in case of an error
    }

    if (query.next()) {
        total_money = query.value("total_money").toInt();
    }

    return total_money;
}

QMap<QDateTime, int> Database::fetch_money_won_last_week() {
    QMap<QDateTime, int> money_per_day;

    // Calculate the date 7 days ago from the current date
    QDateTime seven_days_ago = QDateTime::currentDateTime().addDays(-7);

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, SUM(money_won) AS money_won "
                  "FROM money_record "
                  "WHERE date_time >= :seven_days_ago "
                  "GROUP BY day");
    query.bindValue(":seven_days_ago", seven_days_ago);

    if (!query.exec()) {
        qDebug() << "Error fetching total money for the last 7 days: " << query.lastError();
        return money_per_day;
    }

    while (query.next()) {
        QDateTime date_time = query.value("day").toDateTime();
        int money_won = query.value("money_won").toInt();
        money_per_day.insert(date_time, money_won);
    }

    return money_per_day;
}

QMap<QDateTime, int> Database::fetch_wins_last_week() {
    QMap<QDateTime, int> wins;

    // Calculate the date 7 days ago from the current date
    QDateTime seven_days_ago = QDateTime::currentDateTime().addDays(-7);

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, COUNT(*) AS rounds_won "
                  "FROM win_record "
                  "WHERE round_won = 1 AND date_time >= :seven_days_ago "
                  "GROUP BY day");
    query.bindValue(":seven_days_ago", seven_days_ago);

    if (query.exec()) {
        while (query.next()) {
            QDateTime date_time = query.value("day").toDateTime();
            int rounds_won = query.value("rounds_won").toInt();
            wins.insert(date_time, rounds_won);
        }
    } else {
        qDebug() << "Error fetching wins in the last 7 days: " << query.lastError();
    }

    return wins;
}

QMap<QDateTime, int> Database::fetch_losses_last_week() {
    QMap<QDateTime, int> losses;

    // Calculate the date 7 days ago from the current date
    QDateTime seven_days_ago = QDateTime::currentDateTime().addDays(-7);

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, COUNT(*) AS rounds_lost "
                  "FROM win_record "
                  "WHERE round_won = 0 AND date_time >= :seven_days_ago "
                  "GROUP BY day");
    query.bindValue(":seven_days_ago", seven_days_ago);

    if (query.exec()) {
        while (query.next()) {
            QDateTime date_time = query.value("day").toDateTime();
            int rounds_lost = query.value("rounds_lost").toInt();
            losses.insert(date_time, rounds_lost);
        }
    } else {
        qDebug() << "Error fetching losses in the last 7 days: " << query.lastError();
    }

    return losses;
}

int Database::fetch_total_wins_all_time() {
    int total_wins = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS total_wins FROM win_record WHERE round_won = 1");

    if (query.exec() && query.next()) {
        total_wins = query.value("total_wins").toInt();
    } else {
        qDebug() << "Error fetching total wins: " << query.lastError();
    }

    return total_wins;
}

int Database::fetch_total_losses_all_time() {
    int total_losses = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS total_losses FROM win_record WHERE round_won = 0");

    if (query.exec() && query.next()) {
        total_losses = query.value("total_losses").toInt();
    } else {
        qDebug() << "Error fetching total losses: " << query.lastError();
    }

    return total_losses;
}
