#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "Include/studyform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonLogin_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushButtonsMode_clicked();
    void on_pushButtonPage_clicked();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

private:
    Ui::MainWindow *ui;
    QPoint mPosition;
    StudyForm *studyForm;
};
#endif // MAINWINDOW_H
