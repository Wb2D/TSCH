#ifndef DIALOGMAIL_H
#define DIALOGMAIL_H

#include <QDialog>
#include <QMouseEvent>
#include <QtNetwork>
#include <QSslSocket>

#include "Include/notificationform.h"
#include "HammingCodeEngine/DataWorker/NumberGenerator/numberGenerator.h"




namespace Ui {
class DialogMail;
}

/*!
 * \brief Класс DialogMail предназначен для подтверждения указазанного оператором адреса почт.
 * \author Wb2D.
 * \date 14 марта 2024
 * \warning Система должна иметь доступ к SMPT-серверу Google.
 * \details Данный класс определяет окно, содержащее поле для ввода кода, что отправляется на
 * указанный пользователем адрес электронной почты. Для генерации кода используется класс
 * NumberGenerator из проекта HammingCodeEngine, где для генерации десятириичная СС и восемь
 * разрядов в числе; для отправки был написан и собран в .exe файл скрипт на ЯП Python.
 * Отправка письма на почту организована на основе сетевого протокола SMTP, предназначенного
 * для передачи электронной почты в сетях TCP/IP.
 * Если пользователь вводит неверный пароль, то система сообщает об этом пользователю, генерирует
 * новый код и отправляет новое письмо пользователю на почту.
 * Если система не имеет доступ к SMPT-серверу, то система уведомляет пользователя, что регистрация
 * в данный момент невозможна.
*/

class DialogMail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMail(const QString&, QWidget *parent = nullptr);
    ~DialogMail();

signals:
    void accepted(); ///< сигнал, разрешающий регистрацию пользователя

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
    bool aFlag; ///< флаг определяющий принимается действие или нет
    QPoint mPosition; ///< позиция указателя мыши
    QString email;
    QString code;
};


#endif // DIALOGMAIL_H
