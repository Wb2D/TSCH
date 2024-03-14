#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

#include "Include/mainwindow.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.0.103");
    db.setDatabaseName("TSCHdb");
    db.setUserName("system");
    db.setPassword("6gVD!3Rfdi)kjJ9289+VMN1~!C,fdmD+%VNJ!gh15+h");

    if(db.open()){
        qDebug() << "Database Open!";
    } else {
        qDebug() << "Database NOT Open!";
    }
    */

    MainWindow w;
    w.show();
    return a.exec();
}
