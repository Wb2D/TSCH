#ifndef DIALOGMAIL_H
#define DIALOGMAIL_H

#include <QDialog>
#include <QMouseEvent>
#include <QtNetwork>
#include <QSslSocket>

// нужно будет поменять путь при полноценном внедрении
#include "Tmp/numberGenerator.h"

namespace Ui {
class DialogMail;
}

/*!
 * \brief The DialogMail class
 *
 *
 *
 */

class DialogMail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMail(const QString&, QWidget *parent = nullptr);
    ~DialogMail();

signals:
    void accepted();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void sendMail();

    Ui::DialogMail *ui;
    bool aFlag;
    QPoint mPosition;
    QString email;
    QString code;
};

#endif // DIALOGMAIL_H
