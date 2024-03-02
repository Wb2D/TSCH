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
    void on_pushButtonClose_clicked();
    void on_pushButtonLogin_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushButtonsMode_clicked();
    void on_pushButtonPage_clicked();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;

private:
    Ui::MainWindow *ui;
    StudyForm *studyForm;

    bool aFlag;
    QPoint mPosition;
    QRect wGeometry;
    bool wFlag;

};
#endif // MAINWINDOW_H
