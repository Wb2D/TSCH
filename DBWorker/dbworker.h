#define DBWORKER_H
#ifdef DBWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class DatabaseWorker : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseWorker(QObject *parent = nullptr);
    ~DatabaseWorker();

    bool connectToDB();
    void closeDB();

private:
    QSqlDatabase database;
};

#endif // DBWORKER_H
