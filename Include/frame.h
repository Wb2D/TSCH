#define FRAME_H
#ifdef FRAME_H

#include <QApplication>
#include <QtWidgets>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>



/*!
 * \brief Класс Frame представляет собой масштабируемый и перемещаемый фрейм.
 * \author Wb2D
 * \date 3 марта 2024
 * \details Данный класс позволяет создать фрейм с возможностью масштабирования
 * и перемещения. Также он может быть установлен в QStackedWidget.
 * Скорее всего масштабирование и перемещение использоваться не будут, так что
 * это по сути обычный фрэйм с тенью.
*/

class Frame : public QFrame {
public:
    Frame(QWidget *parent = nullptr);
    ~Frame();

    void setStackedWidget(QStackedWidget*);
    void setFlag(bool);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QStackedWidget* area;
    bool flagChange; ///< Разрешает изменение объекта (перемещение и масштабирование)
    bool flagResize; ///< Изменять размер объекта можно только за правую или нижнюю часть.
    QPoint mPosition;
    QSize wSize;
    static const int SIZE_BORDER = 15; ///< граница за которую можно масштабировать
};


#endif // FRAME_H
