#include "Include/dialogmail.h"
#include "ui_dialogmail.h"




DialogMail::DialogMail(const QString &data, QWidget *parent)
    : QDialog(parent, Qt::Window | Qt::FramelessWindowHint), ui(new Ui::DialogMail) {
    ui->setupUi(this);
    aFlag = false;
    email = data;
    this->code = NumberGenerator::generate(10, 8);
    sendMail();
}


DialogMail::~DialogMail() {
    delete ui;
}



void DialogMail::on_pushButton_clicked() {
    if(!QString::compare(ui->lineEditCode->text(), code)) {
        emit accepted();
    } else {
        /// \todo вывести уведомление, что код неверный и был отправлен новый
        code = NumberGenerator::generate(10, 8);
        sendMail();
    }
}


void DialogMail::on_pushButton_2_clicked() {
    this->close();
}


void DialogMail::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    if (event->button() == Qt::LeftButton) {
        if (event->y() < 30 && event->x() < this->width() - 120) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
            aFlag = true;
        } else {
            aFlag = false;
        }
        this->setFocus();
    }
}


void DialogMail::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        move(event->globalPos() - mPosition);
    }
}


void DialogMail::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; /// cброс флага части окна
    }
}


void DialogMail::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


void DialogMail::on_pushButtonClose_clicked() {
    this->close();
}


void DialogMail::sendMail() {
    QProcess process;
    process.start("C:/Qt/Projects/TSCH/Scripts/sendMail.exe", QStringList() << email << code);
    // Ожидание завершения выполнения скрипта
    process.waitForFinished();
    if(!process.exitCode()) {
        /// \todo уведомление об ошибке подключения к службе SMPT
        this->close();
    }
}

