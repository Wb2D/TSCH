#include "Include/testform.h"
#include "ui_testform.h"




const QString TestForm::TRUE_ANS = QString { "Верно" };
const QString TestForm::WRONG_ANS = QString { "Неверно" };


/*!
 * \brief Конструктор класса TestForm, где создается окно для тестирования.
 * \param parent Родительский виджет.
 * \return Отсутствуют.
*/
TestForm::TestForm(QWidget *parent) :
    QWidget(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::TestForm) {
    ui->setupUi(this);
    ui->frame_1->setStackedWidget(ui->stackedWidget);
    setWindowOpacity(0.98);
    mPosition = QPoint();
    aFlag = false;
    askiiHelper = new AskiiHelper();
    QObject::connect(askiiHelper, &AskiiHelper::closed, this, [=]() {
        askiiHelper->hide();
    });
    QString data = QString("Дано следующее число в шестнадцатеричной системе счисления: ");
    QString number = Converter::toHexadecimal(NumberGenerator::generate(2, 11), 2);
    BitSequence seq;
    Converter::toBinary(seq, number, 16);
    data += number + ". Перевиде его в двоичную систему счисления и закодируйте кодом Хэмминга(";
    if(NumberGenerator::number(0, 1)) {
        answer1 = Encoder1511::start(seq).getSecond();
        data += "15-11). ";
    } else {
        answer1 = Encoder1611::start(seq).getSecond();
        data += "16-11). ";
    }
    number = Converter::toHexadecimal(NumberGenerator::generate(2, 11), 2);
    Converter::toBinary(seq, number, 16);
    answer2 = number;
    data += "В качестве ответа предоставьте закодированную битовую последовательность.";
    ui->labelTask1->setText(data);
    data = "Получена битовая последовательность, представляющая собой число в шестнадцатеричной системе"
           " счисления, закодированное кодом Хэмминга(";
    BitSequenceShell seqShell;
    if(NumberGenerator::number(0, 1)) {
        seqShell = Encoder1511::start(seq);
        seqShell.addError(0, NumberGenerator::number(0, 14));
        data += "15-11):\n ";
    } else {
        seqShell = Encoder1611::start(seq);
        seqShell.addError(0, NumberGenerator::number(0, 15));
        data += "16-11):\n ";
    }
    data += seqShell.getSecond() + ".\n Декодируйте полученную последовательность и в качестве ответа "
                                   "запишите исходное число в шестнадцатеричной системе счисления.";
    ui->labelTask2->setText(data);
    data = "Дан следующий текст: \n";
    QString text = NumberGenerator::generate(2);
    data += text + "\nЗакодируйте его с помощью кода Хэмминга(";
    Converter::toBinary(seq, text);
    if(NumberGenerator::number(0, 1)) {
        answer3 = Encoder74::start(seq).getSecond();
        data += "7-4). ";
    } else {
        answer3 = Encoder84::start(seq).getSecond();
        data += "8-4). ";
    }
    data += " В качестве ответа введите закодированную последовательность бит.";
    ui->labelTask3->setText(data);
}


/*!
 * \brief Деструктор класса TestForm, где освобождаются ресурсы, выделенные для объекта.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
TestForm::~TestForm() {
    delete askiiHelper;
    delete ui;
}


/*!
 * \brief Обработчик нажатия кнопки "Свернуть".
 * \details Минимизирует окно.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void TestForm::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает окно и генерирует сигнал `closed`, который вызывает
 * удаление формы из памяти и открытие начального окна входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void TestForm::on_pushButtonClose_clicked() {
    this->close();
    emit closed();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает окно и генерирует сигнал `closed`, который вызывает
 * удаление формы из памяти и открытие начального окна входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void TestForm::on_pushButtonClose_2_clicked() {
    this->close();
    emit closed();
}


/*!
 * \brief Обработчик нажатия кнопки "Выход".
 * \details Закрывает окно и генерирует сигнал `exited`, который вызывает
 * удаление формы из памяти и выход из приложения.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void TestForm::on_pushButtonExit_clicked() {
    this->close();
    emit exited();
}


/*!
 * \brief Метод для установки статуса обучения.
 * \param status Статус обучения ("В сети"/"Не в сети").
 * \return Отсутствуют.
*/
void TestForm::setStatus(const QString &status) {
    ui->label_2->setText(status);
}


/*!
 * \brief Метод для установки имени пользователя(берется логин в системе).
 * \param user Имя пользователя.
 * \return Отсутствуют.
*/
void TestForm::setUser(const QString &user) {
    ui->label->setText(user);
}


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \param event Событие мыши.
 * \return Отсутствуют.
*/
void TestForm::mousePressEvent(QMouseEvent *event) {
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


/*!
 * \brief Обработчик события перемещения мыши.
 * \param event Событие перемещения мыши.
 * \return Отсутствуют.
*/
void TestForm::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        move(event->globalPos() - mPosition);
    }
}


/*!
 * \brief Обработчик события отпускания кнопки мыши.
 * \param event Событие отпускания кнопки мыши.
 * \return Отсутствуют.
*/
void TestForm::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false;
    }
}


void TestForm::on_pushButtonResult_clicked() {
    int amount = 0;
    QString userAns1 = ui->lineEditAns1_1->text();
    ui->lineEditExpAns1->setText(answer1);
    ui->lineEditResAns1->setText(userAns1);
    if (QString::compare(userAns1, answer1) == 0) {
        ++amount;
        ui->lineEditAns1->setText(TRUE_ANS);
    } else {
        ui->lineEditAns1->setText(WRONG_ANS);
    }
    QString userAns2 = ui->lineEditAns1_2->text();
    ui->lineEditExpAns2->setText(answer2);
    ui->lineEditResAns2->setText(userAns2);
    if (QString::compare(userAns2, answer2) == 0) {
        ++amount;
        ui->lineEditAns2->setText(TRUE_ANS);
    } else {
        ui->lineEditAns2->setText(WRONG_ANS);
    }
    QString userAns3 = ui->lineEditAns1_3->text();
    ui->lineEditExpAns3->setText(answer3);
    ui->lineEditResAns3->setText(userAns3);
    if (QString::compare(userAns3, answer3) == 0) {
        ++amount;
        ui->lineEditAns3->setText(TRUE_ANS);
    } else {
        ui->lineEditAns3->setText(WRONG_ANS);
    }
    /// \todo считать время
    ui->lineEditResult->setText(QString::number(amount) + " / " + "3");
    ui->stackedWidget->setCurrentIndex(1);
}


void TestForm::on_pushButtonHelp_clicked() {
    askiiHelper->show();
}

