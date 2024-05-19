#include <QApplication>
#include <QLockFile>
#include <QDir>

#include "Include/mainwindow.h"
#include "Include/notificationform.h"




/*!
 * \brief Это main файл приложения
 * \author Wb2D
 * \date 27 февраля 2024
 * \details
 * Данный файл содержит основную функцию `main`, которая запускает приложение на основе
 * фреймворка Qt. Приложение использует `QLockFile` для предотвращения повторного запуска
 * приложения на одном устройстве. Если попытка захвата блокировки не удается,
 * создается и отображается окно уведомления `NotificationForm`, информирующее пользователя
 * о том, что приложение уже запущено. В этом случае приложение завершает работу после закрытия
 * уведомления. Если блокировка успешна, запускается основное окно приложения `MainWindow`.
 *
 * Алгоритм работы:
 * 1. Создается экземпляр `QApplication`.
 * 2. Пытается установить блокировку с помощью `QLockFile` для файла "tsch.lock" во временной директории.
 * 3. Если блокировка не удается (приложение уже запущено):
 *    - Создается и отображается окно `NotificationForm` с сообщением о том, что приложение уже запущено.
 *    - Устанавливается соединение для завершения работы приложения после закрытия уведомления.
 * 4. Если блокировка успешна (приложение не запущено):
 *    - Создается и отображается главное окно `MainWindow`.
 * 5. Запускается цикл обработки событий `QApplication`.
*/

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QLockFile lockFile(QDir::temp().absoluteFilePath("tsch.lock"));
    if (!lockFile.tryLock(100)) {
        NotificationForm *notification = new NotificationForm("Приложение уже запущено на вашем устройстве. "
                                                              "Повторный запуск невозможен.");
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, notification, [=]() {
            notification->deleteLater();
            qApp->quit();
        });
        return a.exec();
    } else {
        MainWindow w;
        w.show();
        return a.exec();
    }
}
