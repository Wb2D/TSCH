#include "Include/mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowOpacity(0.975);
    mPosition = QPoint();
    wGeometry = QRect();
    studyForm = new StudyForm();
    dbObj = new DatabaseWorker();
    wFlag = false;
    wFlag = false;
    studyForm->show();
}


MainWindow::~MainWindow() {
    delete dbObj;
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
        move(event->globalPos() - mPosition);
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; /// cброс флага части окна
    }
}


void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) { /// окно во весь экран
    if (event->button() == Qt::LeftButton && event->y() < 30) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(500);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->setStartValue(this->geometry());
        ui->centralwidget->setUpdatesEnabled(false);
        ui->statusbar->setUpdatesEnabled(false);
        if (wFlag) {
            animation->setEndValue(this->wGeometry);
        } else {
            this->wGeometry = this->geometry();
            animation->setEndValue(QApplication::desktop()->availableGeometry());
        }
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            ui->centralwidget->setUpdatesEnabled(true);
            ui->statusbar->setUpdatesEnabled(true);
            this->statusBar()->setSizeGripEnabled(wFlag);
            this->wFlag ^=true;
            delete animation;
        });
        animation->start();
    }
}


void MainWindow::on_pushButtonMinimize_clicked() { /// свернуть окно
    this->showMinimized();
}


void MainWindow::on_pushButtonClose_clicked() { /// закрыть окно
    this->close();
}


void MainWindow::on_pushButtonLogin_clicked() { /// вход в систему
    if(dbObj->connectToDB()) { /// возможно подключиться к серверу
        if(dbObj->authorizationInDB(ui->lineEditLogin_si->text(),
                                    ui->lineEditPassword_si->text())) { /// возможна авторизация
        } else {
            /// \todo нужно уведомить пользователя, что такой учетной записи не сущ-ет
        }
    } else {
        /// \todo нужен переход в оффлайн режим приложения
    }
}


void MainWindow::on_pushButtonReg_clicked() { /// регистрация в приложении
    if(!(ui->lineEditLogin_su->text().isEmpty() || ui->lineEditEmail_su->text().isEmpty() ||
            ui->lineEditPassword_su->text().isEmpty() || ui->lineEditConfPassword_su->text().isEmpty())) {
        if(!QString::compare(ui->lineEditPassword_su->text(),
                             ui->lineEditConfPassword_su->text(), Qt::CaseSensitive)) {
            if(dbObj->connectToDB()) { /// возможно подключиться к серверу
                DialogMail *dialogMail = new DialogMail(ui->lineEditEmail_su->text());
                dialogMail->show();
                connect(dialogMail, &DialogMail::accepted, [this, dialogMail]() {
                    if(dbObj->registerInDB(ui->lineEditLogin_su->text(),
                                           ui->lineEditEmail_su->text(),
                                           ui->lineEditPassword_su->text())) { /// возможна регистрация
                        /// \todo уведомить, что регистрация прошла успешно
                    } else {
                        /// \todo нужно уведомить пользователя, что что-то пошло не так
                    }
                    delete dialogMail;
                });
            } else {
                /// \todo уведомить, что в нет доступа к серверу
            }
        } else {
            /// \todo уведомить, что пароли не совпадают
        }
    } else {
        /// \todo уведомить, что не все поля заполнены
    }
}


void MainWindow::on_pushButtonsMode_clicked() { /// выбор: обучение или тестирование
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton == ui->pushButtonStudy) {
        ui->pushButtonTest->setChecked(false);
    } else if (clickedButton == ui->pushButtonTest) {
        ui->pushButtonStudy->setChecked(false);
    }
}


void MainWindow::on_pushButtonPage_clicked() { /// выбор: авторизация или регистрация
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton == ui->pushButtonSI) {
        ui->pushButtonSI->setChecked(true);
        ui->pushButtonSU->setChecked(false);
    } else if (clickedButton == ui->pushButtonSU) {
        ui->pushButtonSU->setChecked(true);
        ui->pushButtonSI->setChecked(false);
    }
    int index = (clickedButton == ui->pushButtonSI) ? 0 : 1; /// куда переходить
    if(ui->stackedWidget->currentIndex() != index) {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
        ui->stackedWidget->setGraphicsEffect(effect);
        /// анимация для изменения прозрачности
        QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(1000); /// длительность анимации
        animation->setStartValue(1.0); /// начальное значение прозрачности
        animation->setEndValue(0.0); /// конечное значение прозрачности
        /// соединение сигнала завершения анимации с обработчиком
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            ui->stackedWidget->setCurrentIndex(index); /// установить новый индекс
            effect->setOpacity(1.0); /// сброс прозрачности обратно на 1
            delete effect; /// убрать эффект замыливания после использования
        });
        animation->start();
    }
}
