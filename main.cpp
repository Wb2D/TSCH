#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

#include "Include/mainwindow.h"


/*!
 * \brief Это main файл приложения
 * \author Wb2D
 * \date 25 января 2024
 *
 * \todo исправить документирование кода во всех файлах кроме (уже сделал):
 * main.cpp, dbworker.h, dbworker.cp,
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
