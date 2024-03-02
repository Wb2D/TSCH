#define FRAME_H
#ifdef FRAME_H

#include <QApplication>
#include <QtWidgets>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>

#include <QDebug>

class Frame : public QFrame {
public:
    Frame(QWidget *parent = nullptr)
        : QFrame(parent), flag(false) {
        this->setStyleSheet("QFrame { background-color: rgba(80, 80, 105, 0.9); "
                            "border-radius: 35px; border: none;}");
        QGraphicsDropShadowEffect *shEffect = new QGraphicsDropShadowEffect();
        shEffect->setOffset(0, 0);
        shEffect->setColor(QColor(255, 255, 255, 155));
        shEffect->setBlurRadius(15);
        this->setGraphicsEffect(shEffect);
    }

    ~Frame() { delete this->graphicsEffect(); }

    void setStackedWidget(QStackedWidget* stackedWidget) {
        this->area = stackedWidget;
    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            flag = true;
            mPosition = event->pos();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (flag) {
            QPoint delta = event->pos() - mPosition;
            move(pos() + delta);
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            flag = false;
            if (area) {
                bool intersects = false;
                int flagA = area->count();
                qDebug() << QString::number(area->count());
                QRect thisGeometry = geometry();
                for (int i = 0; i < area->count(); ++i) {
                    if (area->widget(i) != this && area->widget(i)->geometry().intersects(thisGeometry)) {

                        intersects = true;
                        break;
                    }
                }
                if (!intersects) {
                    move(mPosition);
                }
            }
        }
    }

private:
    bool flag;
    QPoint mPosition;
    QStackedWidget* area;
};

#endif // FRAME_H
