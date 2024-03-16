#include <QApplication>
#include <QSharedMemory>
#include <QMutex>

#include "Include/mainwindow.h"
#include "Include/notificationform.h"




/*!
 * \brief Это main файл приложения
 * \author Wb2D
 * \date 27 февраля 2024
 * \details Создается объект формы авторизации пользователя в системе, а также реализован механизм
 * контроля повторного запуска системы пользователем.
 * Этот механизм использует мьютекс (mutex) для синхронизации между несколькими экземплярами приложения.
 * При запуске приложение пытается заблокировать мьютекс. Если мьютекс уже заблокирован другим экземпляром,
 * это означает, что приложение уже запущено, а запуск нового экземпляра прерывается.
*/

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMutex mutex(QMutex::Recursive);
    if (!mutex.tryLock()) { ///< попытка заблокировать мьютекс
        NotificationForm *notification = new NotificationForm("Приложение уже запущено на вашем устройстве. "
                                                              "Повторный запуск невозможен.");
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
        return 0;
    }
    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&mutex]() {
        mutex.unlock(); ///< Разблокировка мьютекс
    });
    MainWindow w;
    w.show();
    return a.exec();
}
