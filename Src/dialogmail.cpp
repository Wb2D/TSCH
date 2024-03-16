#include "Include/dialogmail.h"
#include "ui_dialogmail.h"




/*!
 * \brief Конструктор класса DialogMail создает диалоговое окно для ввода кода подтверждения.
 * \param[in] data Данные электронной почты для отправки кода.
 * \param[in] parent Родительский виджет.
 * \return Отсутствуют.
*/
DialogMail::DialogMail(const QString &data, QWidget *parent)
    : QDialog(parent, Qt::Window | Qt::FramelessWindowHint), ui(new Ui::DialogMail) {
    ui->setupUi(this);
    aFlag = false;
    email = data;
    this->code = NumberGenerator::generate(10, 8);
    sendMail();
}


/*!
 * \brief Деструктор класса DialogMail, где освобождаются ресурсы, выделенные для объекта.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
DialogMail::~DialogMail() {
    delete ui;
}


/*!
 * \brief Обработчик нажатия кнопки "OK".
 * \details Если введенный код совпадает с ожидаемым, генерируется сигнал `accepted`, иначе
 * генерируется новый код и отправляется новое письмо, система уведомляют пользователя об этом.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void DialogMail::on_pushButton_clicked() {
    if(!QString::compare(ui->lineEditCode->text(), code)) {
        emit accepted();
    } else {
        NotificationForm *notification = new NotificationForm(
                    "Вы ввели неверный код доступа. Попробуйте снова. Системой был сгенерирован "
                    "и отправлен вам на почту новый код доступа. Ввведите его в соответствующее поле.");
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, notification, &NotificationForm::deleteLater);
        code = NumberGenerator::generate(10, 8);
        sendMail();
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Отмена".
 * \details Закрывает диалоговое окно.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void DialogMail::on_pushButton_2_clicked() {
    this->close();
}


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \details Если нажата левая кнопка мыши в верхней части окна, то устанавливается флаг `aFlag`
 * в значение `true`, чтобы разрешить перемещение окна, иначе в false.
 * \param[in] event Событие мыши.
 * \return Отсутствуют.
*/
void DialogMail::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    if (event->button() == Qt::LeftButton) {
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
 * \details Если нажата левая кнопка мыши и установлен флаг `aFlag`, то окно диалогового окна
 * перемещается в соответствии с позицией указателя мыши.
 * \param[in] event Событие перемещения мыши.
 * \return Отсутствуют.
*/
void DialogMail::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        move(event->globalPos() - mPosition);
    }
}


/*!
 * \brief Обработчик события отпускания кнопки мыши.
 * \details Если отпущена левая кнопка мыши, то сбрасывается флаг `aFlag`, чтобы запретить
 * дальнейшее перемещение окна.
 * \param[in] event Событие отпускания кнопки мыши.
 * \return Отсутствуют.
*/
void DialogMail::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; /// cброс флага части окна
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Свернуть".
 * \details Минимизирует диалоговое окно.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void DialogMail::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает диалоговое окно.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void DialogMail::on_pushButtonClose_clicked() {
    this->close();
}


/*!
 * \brief Метод для отправки письма с кодом на почту.
 * \details Отправляет письмо с подтверждением на определенный в конструкторе адрес
 * электронной почты.  Если отправка письма не завершается успешно, то есть система
 * не имеет подключения к SMPT службе, система уведомляет пользователя об этом и
 * диалоговое окно закрывается.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void DialogMail::sendMail() {
    QProcess process;
    process.start("C:/Qt/Projects/TSCH/Scripts/sendMail.exe", QStringList() << email << code);
    process.waitForFinished(); ///< Ожидание завершения выполнения скрипта
    if(!process.exitCode()) {
        NotificationForm *notification = new NotificationForm(
                    "Системе не удалось установить соединение с SMTP-сервером. Регистрация в"
                    " данный момент недоступна. Вы можете попробовать позже или обратиться к"
                    " администратору");
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, this, [=]() {
            notification->deleteLater();
            this->close();
        });
    }
}
