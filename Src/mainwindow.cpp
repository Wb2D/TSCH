#include "Include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowOpacity(0.975);     // прозрачность окна
    mPosition = QPoint();

    studyForm = new StudyForm();
    studyForm->show();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // был ли клик в верхней части окна
        if (event->y() < 30) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        //  переместить окно только если захвачена верхняя часть
        if (event->y() < 30) {
            move(event->globalPos() - mPosition);
            event->accept();
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

