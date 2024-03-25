#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>




/*!
 * \brief Класс ClickableLabel предназначен для создания метки, которая может реагировать на двойной клик мыши.
 * \author Wb2D
 * \date 23 марта 2024
 * \details Класс ClickableLabel наследуется от QLabel и переопределяет метод mouseDoubleClickEvent для обработки двойного клика мыши.
 * Основные возможности:
 * - Отправка сигнала при двойном клике мыши.
*/

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    /// \brief Конструктор класса.
    explicit ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

signals:
    void doubleClicked(); ///< Сигнал, который отправляется при двойном клике мыши.

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit doubleClicked();
        }
    }
};


#endif // CLICKABLELABEL_H
