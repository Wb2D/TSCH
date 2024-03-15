#include "DBWorker/dbworker.h"
// это нужно будет убрать, когда пропишу класс для контроля ошибок
#include <QDebug>




DatabaseWorker::DatabaseWorker(QObject *parent)
    : QObject(parent) {
    database = QSqlDatabase::addDatabase("QMYSQL");
}


DatabaseWorker::~DatabaseWorker() {
    database.close();
}


QString DatabaseWorker::hashing(const QString &data) const {
    QByteArray hashData = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashData.toHex());
}


bool DatabaseWorker::connectToDB() {
    /// открываю файл config.json для чтения
    QFile file("config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "CANT OPEN config.json";
        return false;
    }
    /// объект JSON-документа
    QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    /// получаю параметры подключения из JSON-объекта, распарсив его
    QString hostName = jsonObj.value("HostName").toString();
    QString databaseName = jsonObj.value("DatabaseName").toString();
    QString userName = jsonObj.value("UserName").toString();
    QString password = jsonObj.value("Password").toString();
    /// установка параметров подключения
    database.setHostName(hostName);
    database.setDatabaseName(databaseName);
    database.setUserName(userName);
    database.setPassword(password);
    if (database.open()) {
        qDebug() << "DB OPEN";
        return true;
    } else {
        qDebug() << "DB NOT OPEN";
        return false;
    }
}


void DatabaseWorker::closeDB() {
    database.close();
}


bool DatabaseWorker::authorizationInDB(const QString &login, const QString &password) {
    if(!database.isOpen()) {
        qDebug() << "DB NOT OPEN";
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE login = :login AND password = :password");
    // добавить хэширование
    query.bindValue(":login", login);
    query.bindValue(":password", hashing(password));
    if(!query.exec()) {
        qDebug() << "ERROR QUERY";
        return false;
    }
    query.next();
    if(query.value(0).toInt()) {
        qDebug() << "LOGIN";
        return true;
    } else {
        qDebug() << "NOT LOGIN";
        return false;
    }
}


bool DatabaseWorker::registerInDB(const QString &login,
                                  const QString &email,
                                  const QString &password) {
    if(!database.isOpen()) {
        qDebug() << "DB NOT OPEN";
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = :email");
    query.bindValue(":email", email);
    if(!query.exec()) {
        qDebug() << "ERROR QUERY";
        return false;
    }
    query.next();
    if(query.value(0).toInt()) {
        qDebug() << "EMAIL USED";
        return false;
    }
    query.prepare("INSERT INTO users (login, email, password) "
                  "VALUES (:login, :email, :password)");
    query.bindValue(":login", login);
    query.bindValue(":email", email);
    query.bindValue(":password", hashing(password));
    if(!query.exec()) {
        qDebug() << "ERROR QUERY";
        return false;
    }
    qDebug() << "REG SUCCES";
    return true;
}
