#include "ErrorTracker/errortracker.h"




const QString ErrorTracker::error1 = QString("Error1");
const QString ErrorTracker::error00 = QString("Error00");
const QString ErrorTracker::error01 = QString("Error01");
const QString ErrorTracker::error02 = QString("Error02");
const QString ErrorTracker::error03 = QString("Error03");
const QString ErrorTracker::error04 = QString("Error04");


/*!
 * \brief Перегруженный оператор присваивания для установки значения ошибки.
 * \param[in] data Новое значение ошибки.
 * \return Ссылка на объект ErrorTracker.
*/
ErrorTracker& ErrorTracker::operator=(const QString &data) {
    this->error = data;
    return *this;
}


/*!
 * \brief Перегруженный оператор сравнения.
 * \param[in] data Новое значение ошибки.
 * \return Переменная типа bool.
*/
bool ErrorTracker::operator==(const QString &data) {
    return (this->error == data);
}
