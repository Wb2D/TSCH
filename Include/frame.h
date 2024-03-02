#define FRAME_H
#ifdef FRAME_H

#include <QApplication>
#include <QtWidgets>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>

class Frame : public QFrame {
public:
    Frame(QWidget *parent = nullptr)
        : QFrame(parent), flagChange(true) {
        this->setStyleSheet("QFrame { background-color: rgba(80, 80, 105, 0.9); "
                            "border-radius: 35px; border: none;}");

        QGraphicsDropShadowEffect *shEffect = new QGraphicsDropShadowEffect();
        shEffect->setOffset(0, 0);
        shEffect->setColor(QColor(255, 255, 255, 155));
        shEffect->setBlurRadius(15);

        this->setGraphicsEffect(shEffect);
    }

    ~Frame() { delete this->graphicsEffect(); }

    void setStackedWidget(QStackedWidget* stackedWidget) { this->area = stackedWidget; }
    void setFlag(bool flag) { this->flagChange = flag; }

protected:

    #include <QDebug>
    void mousePressEvent(QMouseEvent *event) override {
        event->ignore();
        if (event->button() == Qt::LeftButton) {
            mPosition = event->pos(); // Используем pos() вместо globalPos()
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

    void mouseMoveEvent(QMouseEvent *event) override {
        event->ignore();
        if (flagChange) {
            QPoint delta = event->pos() - mPosition; // Используем pos() вместо globalPos()
            if(flagResize) {
                this->resize(wSize + QSize(delta.x(), delta.y()));
            } else {
                this->move(this->pos() + delta); // Используем текущую позицию окна (pos())
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        event->ignore();
                // Обновляем начальную позицию при изменении размера окна
                mPosition = event->pos();
                wSize = this->size();
                flagResize = false;

    }

private:
    QStackedWidget* area;

    bool flagChange;
    bool flagResize;

    QPoint mPosition;
    QSize wSize;

    static const int SIZE_BORDER = 15;
};

#endif // FRAME_H
