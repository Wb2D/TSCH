#define DBWORKER_H
#ifdef DBWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDebug>

#include "Include/global.h"




/*!
 * \brief Класс DatabaseWorker предназначен для работы с удаленной БД
 * \author Wb2D
 * \date 15 марта 2024
 * \warning для установки подключения к удаленному серверу с бд файл config.json
 * должен быть в корневой папке проекта
 *
 * Данный класс содержит набор методов, что необходимы для организации полной
 * работы приложения с удаленной базой данных (в моем случае в качестве сервера
 * выступает виртуальная машина с Ubuntu 22.04.4 и установленной на ней MariaDB).
 * Подключение к серверу осуществляется через служебную учетную запись, данные
 * для подключения хранятся в файле сconfig.json. При передаче паролей осуществляется
 * их хэширование
 *
 *
 *
 * Используемые таблицы имеют следующий вид:
 * `users` (
 *  `id` int(11) NOT NULL AUTO_INCREMENT,
 *  `login` varchar(50) NOT NULL,
 *  `email` varchar(100) NOT NULL,
 *  `password` varchar(255) NOT NULL,
 *  `role` enum('student','teacher','admin') DEFAULT 'student',
 *  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
 *  PRIMARY KEY (`id`),
 *  UNIQUE KEY `login` (`login`),
 *  UNIQUE KEY `email` (`email`))
*/

class DatabaseWorker : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseWorker(QObject *parent = nullptr);
    ~DatabaseWorker();

    bool connectToDB();
    bool authorizationInDB(const QString&, const QString&);
    bool registerInDB(const QString&, const QString&, const QString&);
    void closeDB();

private:
    QString hashing(const QString&) const;
    QSqlDatabase database;
};


#endif // DBWORKER_H
