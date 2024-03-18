#ifndef NOTIFICATIONFORM_H
#define NOTIFICATIONFORM_H

#include <QWidget>
#include <QMouseEvent>




namespace Ui {
class NotificationForm;
}

/*!
 * \brief Класс NotificationForm предназначен для представления оператору обратной связи c системой.
 * \author Wb2D.
 * \date 16 марта 2024
 * \details Данный класс способствует выводу уведомлений со стороны систему пользователю. Они могут
 * включать любой текст, который определяется при создании объекта, чем достигается необходимый уровень
 * гибкости.
*/

class NotificationForm : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationForm(const QString&, QWidget * = nullptr);
    ~NotificationForm();

signals:
    void finished();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private slots:
    void on_pushButtonMinimize_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButton_clicked();

private:
    Ui::NotificationForm *ui;
    bool aFlag; ///< флаг определяющий принимается действие или нет
    QPoint mPosition; ///< позиция указателя мыши
};


#endif // NOTIFICATIONFORM_H
