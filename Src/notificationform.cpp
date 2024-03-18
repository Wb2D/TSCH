#include "Include/notificationform.h"
#include "ui_notificationform.h"




/*!
 * \brief Конструктор класса NotificationForm, где создается объект уведомления с заданным текстом.
 * \param[in] text Текст для отображения в уведомлении.
 * \param[in] parent Родительский виджет.
 * \return Отсутствуют.
*/
NotificationForm::NotificationForm(const QString &text, QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint), ui(new Ui::NotificationForm) {
    ui->setupUi(this);
    aFlag = false;
    ui->label->setText(text);
}


/*!
 * \brief Деструктор класса NotificationForm освобождает ресурсы, выделенные для объекта.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
NotificationForm::~NotificationForm() { delete ui; }


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \details Если нажата левая кнопка мыши в верхней части окна, устанавливает флаг `aFlag` в значение `true`,
 * чтобы разрешить перемещение окна, иначе в false.
 * \param[in] event Событие мыши.
 * \return Отсутствуют.
*/
void NotificationForm::mousePressEvent(QMouseEvent *event) {
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
 * \details Если нажата левая кнопка мыши и установлен флаг `aFlag`,
 * перемещает окно уведомления в соответствии с позицией указателя мыши.
 * \param[in] event Событие перемещения мыши.
 * \return Отсутствуют.
*/
void NotificationForm::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        move(event->globalPos() - mPosition);
    }
}


/*!
 * \brief Обработчик события отпускания кнопки мыши.
 * \details Если отпущена левая кнопка мыши, сбрасывает флаг `aFlag`,
 * чтобы запретить дальнейшее перемещение окна.
 * \param[in] event Событие отпускания кнопки мыши.
 * \return Отсутствуют.
*/
void NotificationForm::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; /// cброс флага части окна
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Свернуть".
 * \details Минимизирует окно уведомления.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void NotificationForm::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает окно уведомления.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void NotificationForm::on_pushButtonClose_clicked() {
    emit finished();
    this->close();
}


/*!
 * \brief Обработчик нажатия кнопки "Ок".
 * \details Закрывает окно уведомления.
 * \param Отсутствуют.
 * \return Отсутствуют
*/
void NotificationForm::on_pushButton_clicked() {
    emit finished();
    this->close();
}
