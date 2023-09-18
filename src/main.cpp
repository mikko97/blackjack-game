#include "mainwindow.hh"
#include "database.hh"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database db;
    bool db_opened = true;
    bool db_tables_created = true;
    const QString error_message = "Database initiation failed. Do you still want "
                                  "to play the game? You won't be able to see any "
                                  "statistics on the amount of money or rounds you "
                                  "have won";

    if(!db.open_database()) {
        db_opened = false;
    }
    if(!db.create_tables()) {
        db_tables_created = false;
    }

    MainWindow w(&db);
    QObject::connect(&w, SIGNAL(db_error_occurred(QString)), &w,
                     SLOT(display_db_initialization_error_dialogue(QString)));

    if(db_opened==false or db_tables_created==false) {
        emit w.db_error_occurred(error_message);
    }

    w.show();
    int result = a.exec();
    return result;
}
