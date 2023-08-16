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

    QString createTableQuery = "CREATE TABLE IF NOT EXISTS win_record ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "user_id INTEGER,"
                              "round_won BOOL,"
                              "date_time DATETIME DEFAULT CURRENT_TIMESTAMP);";

    QString createTableQuery2 = "CREATE TABLE IF NOT EXISTS money_record ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "user_id INTEGER,"
                              "money_won INTEGER,"
                              "date_time DATETIME DEFAULT CURRENT_TIMESTAMP);";

    if (!query.exec(createTableQuery) or !query.exec(createTableQuery2)) {
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

QVector<QPointF> Database::fetch_money_records(int user_id) {
    QVector<QPointF> data_points;

    QSqlQuery query;
    query.prepare("SELECT money_won, date_time FROM money_record WHERE user_id = :user_id");
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error fetching money records: " << query.lastError();
        return data_points;
    }

    while (query.next()) {
        int money_won = query.value("money_won").toInt();
        QDateTime date_time = query.value("date_time").toDateTime();
        data_points.append(QPointF(date_time.toMSecsSinceEpoch(), money_won));
    }

    return data_points;
}

QVector<QPointF> Database::fetch_win_records(int user_id) {
    QVector<QPointF> data_points;

    QSqlQuery query;
    query.prepare("SELECT round_won, date_time FROM win_record WHERE user_id = :user_id");
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error fetching win records: " << query.lastError();
        return data_points;
    }

    while (query.next()) {
        bool round_won = query.value("round_won").toBool();
        QDateTime date_time = query.value("date_time").toDateTime();
        int value = round_won ? 1 : 0;
        data_points.append(QPointF(date_time.toMSecsSinceEpoch(), value));
    }

    return data_points;
}

QMap<QDateTime, int> Database::fetch_total_money_per_day() {
    QMap<QDateTime, int> money_per_day;

    QSqlQuery query;
    query.prepare("SELECT DATE(date_time) AS day, SUM(money_won) AS total_money FROM money_record GROUP BY day");
    //query.prepare("SELECT date_time, SUM(money_won) AS total_money FROM money_record GROUP BY day");

    if (!query.exec()) {
        qDebug() << "Error fetching total money per day: " << query.lastError();
        return money_per_day;
    }

    while (query.next()) {
        QDateTime date_time = query.value("day").toDateTime();
        int total_money = query.value("total_money").toInt();
        money_per_day.insert(date_time, total_money);
    }

    return money_per_day;
}
