#include "DBWorker/dbworker.h"



/*!
 * \brief Конструктор класса DatabaseWorker, где инициализируется объект базы данных.
 * \param[in] parent Родительский объект.
 * \return Отсутствуют.
*/
DatabaseWorker::DatabaseWorker(QObject *parent)
    : QObject(parent) {
    database = QSqlDatabase::addDatabase("QMYSQL");
}


/*!
 * \brief Деструктор класса DatabaseWorker, где закрывается соединение с базой данных.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
DatabaseWorker::~DatabaseWorker() {
    database.close();
}


/*!
 * \brief Метод hashing хэширует входные данные.
 * \details Входные данные хэшируются алгоритмом SHA-256. Это необходимо, чтобы обезопасить
 * учетные записи пользователей.
 * \param[in] data Входные данные для хэширования.
 * \return Хэш в виде строки.
 * \todo Алгоритм хэширование можно заменить на более надежный, например Argon2id с минимальным
 * конфигом в 15 MiB памяти, 2 итерациями и 1 степенью параллелизма.
*/
QString DatabaseWorker::hashing(const QString &data) const {
    QByteArray hashData = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashData.toHex());
}


/*!
 * \brief Метод connectToDB подключается к базе данных.
 * \details При подключении исползуются параметры подключения из файла config.json.
 * Также в случае возникновнения ошибки устанавливается значение G_ERROR.
 * \param Отсутствуют.
 * \return Возвращает true в случае успешного подключения, иначе false.
 * \todo Обезопасить данные для подключения.
*/
bool DatabaseWorker::connectToDB() {
    QFile file("config.json"); ///< открываю файл config.json для чтения
    if (!file.open(QIODevice::ReadOnly)) {
        G_ERROR = ErrorTracker::error1;
        return false;
    }
    QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    QString hostName = jsonObj.value("HostName").toString();
    QString databaseName = jsonObj.value("DatabaseName").toString();
    QString userName = jsonObj.value("UserName").toString();
    QString password = jsonObj.value("Password").toString();
    database.setHostName(hostName);
    database.setDatabaseName(databaseName);
    database.setUserName(userName);
    database.setPassword(password);
    database.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=3");
    if (database.open()) {
        G_ERROR = ErrorTracker::error00;
        return true;
    } else {
        G_ERROR = ErrorTracker::error01;
        return false;
    }
}


/*!
 * \brief Метод closeDB, где закрывается соединение с базой данных.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void DatabaseWorker::closeDB() {
    database.close();
}


/*!
 * \brief Метод authorizationInDB выполняет авторизацию пользователя в базе данных.
 * \param[in] login Логин пользователя.
 * \param[in] password Пароль пользователя.
 * \return Возвращает true, если авторизация успешна, иначе false.
*/
bool DatabaseWorker::authorizationInDB(const QString &login, const QString &password) {
    if(!database.isOpen()) {
        G_ERROR = ErrorTracker::error01;
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE login = :login AND password = :password");
    // добавить хэширование
    query.bindValue(":login", login);
    query.bindValue(":password", hashing(password));
    if(!query.exec()) { ///< Неверный запрос
        G_ERROR = ErrorTracker::error02;
        return false;
    }
    query.next();
    if(query.value(0).toInt()) {
        G_ERROR = ErrorTracker::error00;
        return true;
    } else { ///< Такого пользователя не существует
        G_ERROR = ErrorTracker::error04;
        return false;
    }
}


/*!
 * \brief Метод registerInDB регистрирует нового пользователя в базе данных.
 * \param[in] login Логин нового пользователя.
 * \param[in] email Электронная почта нового пользователя.
 * \param[in] password Пароль нового пользователя.
 * \return Возвращает true в случае успешной регистрации, иначе false.
*/
bool DatabaseWorker::registerInDB(const QString &login,
                                  const QString &email,
                                  const QString &password) {
    if(!database.isOpen()) { ///< Не удалось открыть бд
        G_ERROR = ErrorTracker::error01;
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = :email");
    query.bindValue(":email", email);
    if(!query.exec()) { ///< Неверный запрос
        G_ERROR = ErrorTracker::error02;
        return false;
    }
    query.next();
    if(query.value(0).toInt()) { ///< Пользователь уже зарегестрирован
        G_ERROR = ErrorTracker::error03;
        return false;
    }
    query.prepare("INSERT INTO users (login, email, password) "
                  "VALUES (:login, :email, :password)");
    query.bindValue(":login", login);
    query.bindValue(":email", email);
    query.bindValue(":password", hashing(password));
    if(!query.exec()) {
        G_ERROR = ErrorTracker::error02;
        return false;
    }
    G_ERROR = ErrorTracker::error00;
    return true;
}
