#include "mainwindow.hh"
#include "database.hh"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database db;
    if (db.open_database()) {
        if (!db.create_tables()) {
            qDebug() << "Error creating tables.";
            return 1;
        }

        MainWindow w(&db);
        w.show();

        int result = a.exec();

        return result;
    }

    else {
        qDebug() << "Error opening database.";
        return 1;
    }
}
