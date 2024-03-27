#ifndef ERRORTRACKER_H
#define ERRORTRACKER_H

#include <QString>




/*!
 * \brief Класс ErrorTracker предназначен для упрощения отслеживания ошибок.
 * \author Wb2D.
 * \date 16 марта 2024
 * \details Данный класс определяет список ошибок, который отслеживает система,
 * а также реализует возможность задания значения для отслеживания ошибки.
 * Данный класс в первую очередь предназначен для отслеживания ошибки при переходе
 * между различными объектами системы.
*/

class ErrorTracker
{
public:
    ErrorTracker() { this->error = "error00"; }
    ErrorTracker(const QString &data) { this->error = data; }
    ErrorTracker& operator=(const QString&);
    bool operator==(const QString&);

public:
    static const QString error1; ///< Не удалось открыть файл конфигурации
    static const QString error00; ///< Ошибки не обнаружено.
    static const QString error01; ///< Не удалось открыть БД.
    static const QString error02; ///< Не удалось выполнить запрос к БД.
    static const QString error03; ///< Адрес электронной почты уже использован.
    static const QString error04; ///< Учетная запись не обнаружена

private:
    QString error;
};


#endif // ERRORTRACKER_H
