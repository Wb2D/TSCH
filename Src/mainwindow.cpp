#include "Include/mainwindow.h"
#include "ui_mainwindow.h"




/*!
 * \brief Конструктор класса MainWindow, где инициализируется главное окно приложения.
 * \param[in] parent Родительский виджет.
 * \return Отсутствуют.
*/
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

    /// \todo запретить множественное открытие приложения
}


/*!
 * \brief Деструктор класса MainWindow, где освобождаются ресурсы, выделенные для объекта.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
MainWindow::~MainWindow() {
    delete dbObj;
    delete ui;
    delete studyForm;
}


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \details Если нажата левая кнопка мыши и флаг `wFlag` равен `false`, определяется
 * значение aFlag, отвечающий за возможность перемещения окна.
 * \param[in] event Событие мыши.
 * \return Отсутствуют.
*/
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


/*!
 * \brief Обработчик события перемещения мыши.
 * \details Если нажата левая кнопка мыши и установлен флаг `aFlag`, то окно перемещается.
 * \param[in] event Событие перемещения мыши.
 * \return Отсутствуют.
*/
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        move(event->globalPos() - mPosition);
    }
}


/*!
 * \brief Обработчик события отпускания кнопки мыши.
 * \details Сбрасывает флаг `aFlag`, чтобы запретить дальнейшее перемещение окна.
 * \param[in] event Событие отпускания кнопки мыши.
 * \return Отсутствуют.
*/
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; /// cброс флага части окна
    }
}


/*!
 * \brief Обработчик двойного щелчка мыши.
 * \details Разворчаивает окно во весь экран или возврашает его к последнему размеру.
 * \param[in] event Событие двойного щелчка мыши.
 * \return Отсутствуют.
*/
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
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


/*!
 * \brief Обработчик нажатия кнопки "Свернуть".
 * \details Минимизирует окно входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void MainWindow::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает окно входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void MainWindow::on_pushButtonClose_clicked() {
    this->close();
}


/*!
 * \brief Обработчик нажатия кнопки "Вход".
 * \details Происходит попытка входа в систему, с использованием введенных оператором
 * учетных данных.
 * Если система не может установить соединение с сервером бд и првоерить введенные
 * пользователем данные, то возвращается уведомление и система запускается в оффлайн режиме.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void MainWindow::on_pushButtonLogin_clicked() {
    if(dbObj->connectToDB()) { ///< возможно подключиться к серверу
        if(dbObj->authorizationInDB(ui->lineEditLogin_si->text(),
                                    ui->lineEditPassword_si->text())) { ///< возможна авторизация
            /// \todo здесь нужно открыть studyform, передав в нее логин пользователя; скрыть это окно.
        } else {
            NotificationForm *notification;
            if(G_ERROR == ErrorTracker::error02) {
                notification = new NotificationForm(
                                    "Запрос, отправленный к БД, не был выполнен. Попробуйте снова.");
            } else if(G_ERROR == ErrorTracker::error04) {
                notification = new NotificationForm(
                                    "Не удалось найти учетную запись. Попробуйте снова. В случае повторения ошибки "
                                    "воспользуйтесь восстановлением пароля или обратитесь к администратору.");
            } else if(G_ERROR == ErrorTracker::error01) {
                notification = new NotificationForm(
                                    "Системе не удалось установить соединение с сервером. Попробуйте снова.");
            } else {
                notification = new NotificationForm(
                                    "Возникла непредвиденная ошибка. Попробуйте снова.");
            }
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
            ui->lineEditLogin_si->clear();
            ui->lineEditPassword_si->clear();
        }
    } else {
        NotificationForm *notification;
        if(G_ERROR == ErrorTracker::error1) {
            notification = new NotificationForm(
                                "Системе не удалось получить доступ к файлу конфигурации системы, поэтому подключение "
                                "к базе данных невозможно. Приложение будет автоматически запущено в оффлайн режиме.");
        } else if(G_ERROR == ErrorTracker::error01) {
            notification = new NotificationForm(
                                "Системе не удалось установить соединение с сервером, поэтому приложение "
                                "будет автоматически запущено в оффлайн режиме.");
        } else {
            notification = new NotificationForm(
                                "Возникла непредвиденная ошибка, поэтому приложение будет автоматически запущено в "
                                "оффлайн режиме.");
        }
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
        /// \todo здесь нужно открыть studyform, передав в нее логин "Локальный пользователь"; скрыть это окно.
        /// Причем сделать это в коннекте через лямба-функцию.
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Регистрация".
 * \details Выполняется попытка регистрации пользователя в системе, если удается
 * установить соединение с сервером, иначе оператор получает уведомление, что
 * регистрация невозможна.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void MainWindow::on_pushButtonReg_clicked() {
    if(!(ui->lineEditLogin_su->text().isEmpty() ||
         ui->lineEditEmail_su->text().isEmpty() ||
         ui->lineEditPassword_su->text().isEmpty() ||
         ui->lineEditConfPassword_su->text().isEmpty())) { ///< если все поля заполнены
        if(!QString::compare(ui->lineEditPassword_su->text(),
                             ui->lineEditConfPassword_su->text(), Qt::CaseSensitive)) { ///< пароли совпадают
            if(dbObj->connectToDB()) { ///< возможно подключиться к серверу
                DialogMail *dialogMail = new DialogMail(ui->lineEditEmail_su->text());
                dialogMail->show();
                connect(dialogMail, &DialogMail::accepted, this, [this, dialogMail]()
                {
                    if(dbObj->registerInDB(ui->lineEditLogin_su->text(),
                                           ui->lineEditEmail_su->text(),
                                           ui->lineEditPassword_su->text())) { ///< регистрация прошла успешно
                        NotificationForm *notification = new NotificationForm(
                                    "Поздравляем! Регистрация в системе прошла успешно. Теперь вы можете войти в вашу "
                                    "учетную запись через вкладку \"Авторизация\"");
                        notification->show();
                        QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
                        ui->lineEditLogin_su->clear();
                        ui->lineEditEmail_su->clear();
                        ui->lineEditPassword_su->clear();
                        ui->lineEditConfPassword_su->clear();
                    } else {
                        NotificationForm *notification;
                        if(G_ERROR == ErrorTracker::error01) {
                            notification = new NotificationForm(
                                                "Системе не удалось установить соединение с сервером. Для регистрации обратитесь "
                                                "к администратору.");
                        } else if(G_ERROR == ErrorTracker::error02) {
                            notification = new NotificationForm(
                                                "Запрос, отправленный к бд, не был выполнен. Для регистрации обратитесь "
                                                "к администратору.");
                        } else if(G_ERROR == ErrorTracker::error03) {
                            notification = new NotificationForm(
                                                "Учетная запись с таким адресом электронный почты уже зарегестрирована. "
                                                "Воспользуйтесь авторизацией для входа в систему или, в случае потери пароля, "
                                                "функцией его восстановления.");
                        }
                        else {
                            notification = new NotificationForm(
                                                "Возникла непредвиденная ошибка. Для регистрации обратитесь к администратору.");
                        }
                        notification->show();
                        QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
                    }
                    delete dialogMail;
                });
            } else {
                NotificationForm *notification;
                if(G_ERROR == ErrorTracker::error1) {
                    notification = new NotificationForm(
                                        "Системе не удалось получить доступ к файлу конфигурации системы, поэтому подключение "
                                        "к базе данных невозможно. Для регистрации обратитесь к администратору.");
                } else if(G_ERROR == ErrorTracker::error01) {
                    notification = new NotificationForm(
                                        "Системе не удалось установить соединение с сервером. Для регистрации обратитесь "
                                        "к администратору.");
                } else {
                    notification = new NotificationForm(
                                        "Возникла непредвиденная ошибка. Для регистрации обратитесь к администратору.");
                }
                notification->show();
                QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
                ui->lineEditLogin_su->clear();
                ui->lineEditEmail_su->clear();
                ui->lineEditPassword_su->clear();
                ui->lineEditConfPassword_su->clear();
            }
        } else {
            NotificationForm *notification = new NotificationForm(
                        "Введенные вами пароли не совпадают. Попробуйте снова.");
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
            ui->lineEditPassword_su->clear();
            ui->lineEditConfPassword_su->clear();
        }
    } else {
        NotificationForm *notification = new NotificationForm(
                    "Вы ввели неверные данные для регистрации. Проверьте, что все поля была заполнены.");
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
    }
}


/*!
 * \brief Обработчик выбора режима.
 * \details Выполняет обработку нажатия, определяя в зависимости от нажатой кнопки, каков
 * режим дальнейшей работы приложения: обучение или тестирование.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void MainWindow::on_pushButtonsMode_clicked() { /// выбор: обучение или тестирование
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton == ui->pushButtonStudy) {
        ui->pushButtonTest->setChecked(false);
    } else if (clickedButton == ui->pushButtonTest) {
        ui->pushButtonStudy->setChecked(false);
    }
}


/*!
 * \brief Обработчик выбора интерфейса.
 * \details Выполняет обработку нажатия, меняя отображаемый интерфейс: авторизация или
 * регистрация - в зависимости от нажатой кнопки.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void MainWindow::on_pushButtonPage_clicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton == ui->pushButtonSI) {
        ui->pushButtonSI->setChecked(true);
        ui->pushButtonSU->setChecked(false);
    } else if (clickedButton == ui->pushButtonSU) {
        ui->pushButtonSU->setChecked(true);
        ui->pushButtonSI->setChecked(false);
    }
    int index = (clickedButton == ui->pushButtonSI) ? 0 : 1; ///< куда переходить
    if(ui->stackedWidget->currentIndex() != index) {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
        ui->stackedWidget->setGraphicsEffect(effect);
        QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(1000);
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            ui->stackedWidget->setCurrentIndex(index); ///< установить новый индекс
            effect->setOpacity(1.0); ///< сброс прозрачности обратно на 1
            delete effect; ///< убрать эффект замыливания после использования
        });
        animation->start();
    }
}
