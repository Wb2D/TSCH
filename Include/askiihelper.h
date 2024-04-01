#ifndef ASKIIHELPER_H
#define ASKIIHELPER_H

#include <QWidget>
#include <QMouseEvent>



namespace Ui {
class AskiiHelper;
}

class AskiiHelper : public QWidget
{
    Q_OBJECT

public:
    explicit AskiiHelper(QWidget *parent = nullptr);
    ~AskiiHelper();

signals:
    void closed();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private slots:
    void on_pushButtonMinimize_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::AskiiHelper *ui;

    QPoint mPosition;
    bool aFlag;
};

#endif // ASKIIHELPER_H
