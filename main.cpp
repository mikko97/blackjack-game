#include "mainwindow.hh"
#include "database.hh"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database db;
    if (db.open_database()) {
        // Create tables if they don't exist
        if (!db.create_tables()) {
            qDebug() << "Error creating tables.";
            return 1;
        }

        // Check if the initial record exists for the user
        int user_id = 1; // Replace with the actual user ID
        bool initial_record_exists = db.check_initial_record_exists(user_id);

        if (!initial_record_exists) {
            // Insert initial record for the user
            if (db.insert_initial_record(user_id)) {
                qDebug() << "Initial record inserted.";
            }
            else {
                qDebug() << "Error inserting initial record.";
            }
        }

        MainWindow w(&db);
        w.show();

        int result = a.exec();

        return result;
    } else {
        // Handle database opening error
        return 1;
    }
}
