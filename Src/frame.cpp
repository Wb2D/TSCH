#include "Include/frame.h"




/*!
 * \brief Конструктор класса Frame, где инициализируется внешний вид и эффекты окна.
 * \param[in] parent Родительский объект.
 * \return Отсутствуют.
*/
Frame::Frame(QWidget *parent)
    : QFrame(parent), flagChange(false) {
    this->setStyleSheet("QFrame { background-color: rgba(80, 80, 105, 0.9); "
                        "border-radius: 35px; border: none;}");
    QGraphicsDropShadowEffect *shEffect = new QGraphicsDropShadowEffect();
    shEffect->setOffset(0, 0);
    shEffect->setColor(QColor(255, 255, 255, 155));
    shEffect->setBlurRadius(15);
    this->setGraphicsEffect(shEffect);
}


/*!
 * \brief Деструктор класса Frame, где освобождаются ресурсы, выделенные для объекта.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
Frame::~Frame() {
    delete this->graphicsEffect();
}


/*!
 * \brief Метод setStackedWidget, где устанавливается указатель на QStackedWidget.
 * \param[in] stackedWidget Указатель на QStackedWidget.
 * \return Отсутствуют.
*/
void Frame::setStackedWidget(QStackedWidget* stackedWidget) {
    this->area = stackedWidget;
}


/*!
 * \brief Метод setFlag, где устанавливается флаг изменения окна.
 * \param[in] flag Флаг изменения окна.
 * \return Отсутствуют.
*/
void Frame::setFlag(bool flag) {
    this->flagChange = flag;
}


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \details Обрабатывает нажатие левой кнопки мыши для перемещения или изменения размера окна.
 * \param[in] event Событие мыши.
 * \return Отсутствуют.
*/
void Frame::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    if (event->button() == Qt::LeftButton) {
        mPosition = event->pos();
        wSize = this->size();
        if(( event->x() > this->width() - SIZE_BORDER ||
             event->y() > this->height() - SIZE_BORDER) &&
            (this->x() < this->area->width() && this->y() < this->area->height())) {
            flagResize = true;
        } else {
            flagResize = false;
        }
    }
    this->setFocus();
}


/*!
 * \brief Обработчик события перемещения мыши.
 * \details Перемещает окно или изменяет его размер в зависимости от флагов.
 * \param[in] event Событие перемещения мыши.
 * \return Отсутствуют.
*/
void Frame::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (flagChange) {
        QPoint delta = event->pos() - mPosition;
        if(flagResize) {
            this->resize(wSize + QSize(delta.x(), delta.y()));
        } else {
            this->move(this->pos() + delta);
        }
    }
}


/*!
 * \brief Обработчик события отпускания кнопки мыши.
 * \details Сбрасывает флаг изменения размера окна.
 * \param[in] event Событие отпускания кнопки мыши.
 * \return Отсутствуют.
*/
void Frame::mouseReleaseEvent(QMouseEvent *event) {
    event->ignore();
    mPosition = event->pos();
    wSize = this->size();
    flagResize = false;
}
