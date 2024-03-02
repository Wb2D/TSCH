#include "Include/mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowOpacity(0.975);
    mPosition = QPoint();
    wGeometry = QRect();
    studyForm = new StudyForm();
    wFlag = false;
    wFlag = false;
    studyForm->show();
}


MainWindow::~MainWindow() {
    delete ui;
    delete studyForm;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    if (event->button() == Qt::LeftButton && !wFlag) {
        if (event->y() < 30 && event->x() < this->width() - 120) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
            aFlag = true;
        } else {
            aFlag = false;
        }
        this->setFocus();
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        //  переместить окно только если захвачена НУЖНА часть окна
            move(event->globalPos() - mPosition);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; // cброс флага части окна
    }
}


void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->y() < 30) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(500);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->setStartValue(this->geometry());
        ui->centralwidget->setUpdatesEnabled(false);
        if (wFlag) {
            animation->setEndValue(this->wGeometry);
        } else {
            this->wGeometry = this->geometry();
            animation->setEndValue(QApplication::desktop()->availableGeometry());
        }
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            ui->centralwidget->setUpdatesEnabled(true);
            this->statusBar()->setSizeGripEnabled(wFlag);
            this->wFlag ^=true;
            delete animation;
        });
        animation->start();
    }
}


// свернуть окно
void MainWindow::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


// закрыть окно
void MainWindow::on_pushButtonClose_clicked() {
    this->close();
}


// вход пользователя в систему
void MainWindow::on_pushButtonLogin_clicked() {

}


/* Здесь добавить регистрацию в приложении */


// запуск обучения или тестирования
void MainWindow::on_pushButtonsMode_clicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton == ui->pushButtonStudy) {
        ui->pushButtonTest->setChecked(false);
    } else if (clickedButton == ui->pushButtonTest) {
        ui->pushButtonStudy->setChecked(false);
    }
}


// выбор: авторизация или регистрация
void MainWindow::on_pushButtonPage_clicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton == ui->pushButtonSI) {
        ui->pushButtonSI->setChecked(true);
        ui->pushButtonSU->setChecked(false);
    } else if (clickedButton == ui->pushButtonSU) {
        ui->pushButtonSU->setChecked(true);
        ui->pushButtonSI->setChecked(false);
    }
    int index = (clickedButton == ui->pushButtonSI) ? 0 : 1; // куда переходить
    if(ui->stackedWidget->currentIndex() != index) {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
        ui->stackedWidget->setGraphicsEffect(effect);
        // Анимация для изменения прозрачности
        QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(1000); // длительность анимации
        animation->setStartValue(1.0); // начальное значение прозрачности
        animation->setEndValue(0.0); // конечное значение прозрачности
        // соединение сигнал завершения анимации с обработчиком
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            ui->stackedWidget->setCurrentIndex(index); // установить новый индекс
            effect->setOpacity(1.0); // сброс прозрачности обратно на 1
            delete effect; // убрать эффект замыливания после использования
        });
        // запуск анимации
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

