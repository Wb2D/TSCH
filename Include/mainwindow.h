#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QAbstractAnimation>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QScreen>

#include "Include/studyform.h"
#include "Include/dialogmail.h"
#include "Include/notificationform.h"
#include "DBWorker/dbworker.h"
#include "Include/global.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Класс MainWindow предназначен для предоставления оператору интерфейса входа в систему.
 * \author Wb2D.
 * \date 28 февраля 2024
 * \warning Для авторизации/регистрации система должна иметь доступ к серверу.
 * \details Класс MainWindow обеспечивает возможности взаимодействия пользователя с системой, а именно -
 * авторизации/регистрации в ней. Этот интерфейс позволяет пользователю произвести вход в систему для
 * получения доступа к функционалу и, при необходимости, зарегистрировать новый аккаунт. При отсутствии
 * доступа к серверу, приложение будет запущено в оффлайн режиме.
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonLogin_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushButtonsMode_clicked();
    void on_pushButtonPage_clicked();
    void on_pushButtonReg_clicked();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    //void mouseDoubleClickEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void advanceMode(const QString&, const QString&);

    enum ModeFlag {
        NO_MODE,
        STUDY_MODE,
        TEST_MODE,
    } mFlag; ///< флаг режима;

    Ui::MainWindow *ui;
    DatabaseWorker *dbObj; ///< объект подключения к бд
    bool aFlag; ///< был ли совершен клик в допустимой области
    QPoint mPosition;
    //QRect wGeometry;
    //bool wFlag; ///< флаг окна: оконное или во весь экран
};


#endif // MAINWINDOW_H
