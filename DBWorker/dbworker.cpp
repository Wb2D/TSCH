#include "DBWorker/dbworker.h"




DatabaseWorker::DatabaseWorker(QObject *parent)
    : QObject(parent) {
    database = QSqlDatabase::addDatabase("QMYSQL");
}


DatabaseWorker::~DatabaseWorker() {
    database.close();
}


#include <QDebug>
bool DatabaseWorker::connectToDB() {
    // открываю файл config.json для чтения
    QFile file("config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "NOT OPEN";
        return false;
    }
    // объект JSON-документа
    QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    // Получаем параметры подключения из JSON-объекта
    QString hostName = jsonObj.value("HostName").toString();
    QString databaseName = jsonObj.value("DatabaseName").toString();
    QString userName = jsonObj.value("UserName").toString();
    QString password = jsonObj.value("Password").toString();
    // Устанавливаем параметры подключения
    database.setHostName(hostName);
    database.setDatabaseName(databaseName);
    database.setUserName(userName);
    database.setPassword(password);
    // Открываем базу данных
    if (database.open()) {
        qDebug() << "Y";
        return true;
    } else {
        qDebug() << "N";
        return false;
    }
}


void DatabaseWorker::closeDB() {
    database.close();
}
