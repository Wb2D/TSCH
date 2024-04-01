#include "Include/askiihelper.h"
#include "ui_askiihelper.h"





AskiiHelper::AskiiHelper(QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::AskiiHelper) {
    ui->setupUi(this);
    setWindowOpacity(0.975);
    mPosition = QPoint();
    aFlag = false;
}


AskiiHelper::~AskiiHelper()
{
    delete ui;
}


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \details Если нажата левая кнопка мыши и флаг `wFlag` равен `false`, определяется
 * значение aFlag, отвечающий за возможность перемещения окна.
 * \param[in] event Событие мыши.
 * \return Отсутствуют.
*/
void AskiiHelper::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    if (event->button() == Qt::LeftButton /*&&!wFlag*/) {
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
void AskiiHelper::mouseMoveEvent(QMouseEvent *event) {
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
void AskiiHelper::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; /// cброс флага части окна
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Свернуть".
 * \details Минимизирует окно.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void AskiiHelper::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает окно и генерирует сигнал `closed`, который вызывает
 * удаление формы из памяти и открытие начального окна входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void AskiiHelper::on_pushButtonClose_clicked() {
    this->close();
    emit closed();
}
