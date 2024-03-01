#include "Include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowOpacity(0.975);
    mPosition = QPoint();
    studyForm = new StudyForm();
    studyForm->show();
    wPosition = QPoint();
    wSize = QSize();
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // был ли клик в верхней части окна
        if (event->y() < 30 && !isFullScreen() && event->x() < frameGeometry().width() - 140) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
        }
        this->setFocus();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        //  переместить окно только если захвачена верхняя часть
        if (event->y() < 30 && !isFullScreen()) {
            move(event->globalPos() - mPosition);
            event->accept();
        }
    }
}

#include <QDebug>

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->y() < 30) {
        if (isFullScreen()) {
            //ui->centralwidget->setUpdatesEnabled(false);
            // анимаци перехода в оконный режим
            //qDebug() << QString::number(size().rheight()) << " " << QString::number(size().rwidth()) << " " << isFullScreen();
            QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
            animation->setDuration(1000);
            animation->setEasingCurve(QEasingCurve::OutCubic);
            animation->setStartValue(QRect(pos(), size()));
            animation->setEndValue(QRect(wPosition, wSize));
            qDebug() << "B" << QString::number(size().rheight()) << " " << QString::number(size().rwidth()) << " " << isFullScreen();
            connect(animation, &QPropertyAnimation::finished, this, [this, animation]() {
                qDebug() << "A" << QString::number(size().rheight()) << " " << QString::number(size().rwidth()) << " " << isFullScreen();
                delete animation;
            });
            //animation->setDirection(QAbstractAnimation::Forward);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
            //showNormal();
        } else {
            wSize = size();
            wPosition = pos();
            // анимаци перехода в полноэкранный режим
            /*
            qDebug() << QString::number(size().rheight()) << " " << QString::number(size().rwidth()) << " " << isFullScreen();
            wSize = size();
            wPosition = pos();
            animation->setEndValue(QGuiApplication::primaryScreen()->availableGeometry());
            connect(animation, &QPropertyAnimation::finished, this, [this]() {
                //setUpdatesEnabled(true);
                ui->centralwidget->setUpdatesEnabled(true);
                showFullScreen();
            });
            */
            showFullScreen();
        }

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
        connect(animation, &QPropertyAnimation::finished, [=]() {
            ui->stackedWidget->setCurrentIndex(index); // установить новый индекс
            effect->setOpacity(1.0); // сброс прозрачность обратно на 1
            delete effect; // убрать эффект замыливания после использования
        });
        // запуск анимации
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

