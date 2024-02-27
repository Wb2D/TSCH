#include "Include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowOpacity(0.98);     // прозрачность окна
    mPosition = QPoint();
    //studyForm = new StudyForm();
    // подключение к слоту запуска mainwindow по кнопке в studyform (возвращение)
    //connect(studyForm, &StudyForm::openMainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow() { delete ui; }

// вход в систему
void MainWindow::on_pushButton_clicked() {
    ui->lineEditPassword->clear();
    //studyForm->show();
    this->close();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // перемещаю окно на новую позицию
        move(event->globalPos() - mPosition);
        event->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        // считываю позицию, в которой была нажата кнопка мыши
        mPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}
