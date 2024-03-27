#include "Include/studyform.h"
#include "ui_studyform.h"




const QRegularExpression StudyForm::LEADING_REGEX("^0+");
const QRegularExpression StudyForm::BINARY_REGEX("^[01]+$");
const QRegularExpression StudyForm::QUATERNARY_REGEX("^[0-3]+$");
const QRegularExpression StudyForm::OCTAL_REGEX("^[0-7]+$");
const QRegularExpression StudyForm::DECIMAL_REGEX("^[0-9]+$");
const QRegularExpression StudyForm::HEXADECIMAL_REGEX("^[0-9A-F]+$");


/*!
 * \brief Конструктор класса StudyForm, где создается окно для обучения.
 * \param parent Родительский виджет.
 * \return Отсутствуют.
*/
StudyForm::StudyForm(QWidget *parent) :
    QWidget(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::StudyForm) {
    ui->setupUi(this);
    setWindowOpacity(0.98);
    mPosition = QPoint();
    aFlag = false;
    encodeInputFlag = NO_MODE;
    encodeTypeFlag = NO_TYPE;
    encodeNumberFlag = NO_SYSTEM;
    encodeAlgFlag = NO_ALG;
    noiseInputFlag = NO_MODE;
    noiseErrorFlag = NO_ERR;
    noiseImpactFlag = NO_IMPACT;
    decodeTypeFlag = NO_TYPE;
    decodeNumberFlag = NO_SYSTEM;
    decodeAlgFlag = NO_ALG;
    bitSeq = BitSequence();
    clearEncodedBitSeq = BitSequenceShell();
    modEncodedBitSeq = BitSequenceShell();
    bigInt = BigInteger();
    clearEncodedBigInt = BigIntegerShell();
    modEncodedBigInt = BigIntegerShell();
    decodedBitData = QPair<BitSequenceShell, QVector<BitSequence>>();
    decodedIntData = QPair<BigIntegerShell, QVector<BigInteger>>();
    ui->frame_6->setStackedWidget(ui->stackedWidget);
    ui->frame_4->setStackedWidget(ui->stackedWidget);
    ui->frame_5->setStackedWidget(ui->stackedWidget);
    ui->frame_7->setStackedWidget(ui->stackedWidget);
    ui->frame_9->setStackedWidget(ui->stackedWidget);
    ui->frame_10->setStackedWidget(ui->stackedWidget);
    ui->frame_12->setStackedWidget(ui->stackedWidget);
    ui->frame_20->setStackedWidget(ui->stackedWidget);
    ui->frame_16->setStackedWidget(ui->stackedWidget);
    ui->frame_13->setStackedWidget(ui->stackedWidget);
    ui->frame_15->setStackedWidget(ui->stackedWidget);
    ui->frame_18->setStackedWidget(ui->stackedWidget);
    ui->frame_14->setStackedWidget(ui->stackedWidget);
    ui->frame_17->setStackedWidget(ui->stackedWidget);
    ui->frame_22->setStackedWidget(ui->stackedWidget);
    ui->frame_28->setStackedWidget(ui->stackedWidget);
    ui->frame_29->setStackedWidget(ui->stackedWidget);
    ui->frame_24->setStackedWidget(ui->stackedWidget);
    ui->frame_21->setStackedWidget(ui->stackedWidget);
    ui->frame_27->setStackedWidget(ui->stackedWidget);
    ui->frame_26->setStackedWidget(ui->stackedWidget);
    connect(ui->textEditData, &QTextEdit::textChanged, this, [=]() {
        resetEncoderData();
    });
    connect(ui->textEditData_2, &QTextEdit::textChanged, this, [=]() {
        resetDecoderData();
    });
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        setBitsEncoding(ui->listWidget->count() - ui->listWidget->row(item) - 1);
    });
    connect(ui->listWidget_2, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        setBitsNoise(ui->listWidget_2->count() - ui->listWidget_2->row(item) - 1, false);
    });
    connect(ui->listWidget_3, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        setBitsDecoding(ui->listWidget_3->count() - ui->listWidget_3->row(item) - 1);
    });
}


/*!
 * \brief Деструктор класса StudyForm, где освобождаются ресурсы, выделенные для объекта.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
StudyForm::~StudyForm() { delete ui; }


/*!
 * \brief Метод для установки тени на виджет.
 * \param widget Виджет, на который будет установлена тень.
 * \return Отсутствуют.
*/
void StudyForm::setShadow(QWidget *widget) {
    QGraphicsDropShadowEffect *shEffect = new QGraphicsDropShadowEffect();
    shEffect->setOffset(0, 0);
    shEffect->setColor(QColor(255, 255, 255, 155));
    shEffect->setBlurRadius(15);
    widget->setGraphicsEffect(shEffect);
}


/*!
 * \brief Метод для установки эффекта размытия на виджет.
 * \param widget Виджет, на который будет установлен эффект размытия.
 * \param blurRadius Радиус размытия.
 * \return Отсутствуют.
*/
void StudyForm::setBlur(QWidget *widget, int blurRadius) {
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect(widget);
    effect->setBlurRadius(blurRadius);
    effect->setBlurHints(QGraphicsBlurEffect::AnimationHint);
    widget->setGraphicsEffect(effect);
}


/*!
 * \brief Метод для удаления эффекта с виджета.
 * \param widget Виджет, с которого будет удален эффект.
 * \return Отсутствуют.
*/
void StudyForm::removeEffect(QWidget *widget) {
    delete widget->graphicsEffect();
    widget->setGraphicsEffect(nullptr);
}


/*!
 * \brief Метод для установки статуса обучения.
 * \param status Статус обучения ("В сети"/"Не в сети").
 * \return Отсутствуют.
*/
void StudyForm::setStatus(const QString &status) {
    ui->label_2->setText(status);
}


/*!
 * \brief Метод для установки имени пользователя(берется логин в системе).
 * \param user Имя пользователя.
 * \return Отсутствуют.
*/
void StudyForm::setUser(const QString &user) {
    ui->label->setText(user);
}


/*!
 * \brief Обработчик события нажатия кнопки мыши.
 * \param event Событие мыши.
 * \return Отсутствуют.
*/
void StudyForm::mousePressEvent(QMouseEvent *event) {
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
void StudyForm::mouseMoveEvent(QMouseEvent *event) {
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
void StudyForm::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false;
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Свернуть".
 * \details Минимизирует окно.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


/*!
 * \brief Обработчик нажатия кнопки "Закрыть".
 * \details Закрывает окно и генерирует сигнал `closed`, который вызывает
 * удаление формы из памяти и открытие начального окна входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonClose_clicked() {
    this->close();
    emit closed();
}


/*!
 * \brief Обработчик нажатия кнопки "Выход".
 * \details Закрывает окно и генерирует сигнал `closed`, который вызывает
 * удаление формы из памяти и открытие начального окна входа в систему.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonClose_2_clicked() {
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
void StudyForm::on_pushButtonExit_clicked() {
    this->close();
    emit exited();
}

/*!
 * \brief Обработчик нажатия кнопки "Выбор формы ввода данных".
 * \details Обрабатывает нажатие кнопки выбора формы ввода данных.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderFormInput_clicked() {
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderFormInput_1) {
        ui->horizontalSliderFormInput_2->setValue(0);
        if(senderSlider->value() == 0) {
            encodeInputFlag = MANUAL;
            ui->textEditData->setReadOnly(false);
        } else {
            encodeInputFlag = NO_MODE;
            ui->textEditData->setReadOnly(true);
        }
        ui->spinBoxAmount->setReadOnly(true);
        ui->pushButtonAutoGen->setEnabled(false);
    } else if (senderSlider == ui->horizontalSliderFormInput_2) {
        ui->horizontalSliderFormInput_1->setValue(0);
        if(senderSlider->value() == 0) {
            encodeInputFlag = GENERATED;
            ui->spinBoxAmount->setReadOnly(false);
            ui->pushButtonAutoGen->setEnabled(true);
        } else {
            encodeInputFlag = NO_MODE;
            ui->spinBoxAmount->setReadOnly(true);
            ui->pushButtonAutoGen->setEnabled(false);
        }
        ui->textEditData->setReadOnly(true);
    }
    bool enableButton = senderSlider == ui->horizontalSliderFormInput_2 ||
            (senderSlider == ui->horizontalSliderFormInput_1 && senderSlider->value() != 0);
    if(enableButton) {
        removeEffect(ui->frame_8);
    } else {
        setBlur(ui->frame_8, BLUR_RADIUS_2);
    }
    ui->frame_8->update();
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор типа входных данных".
 * \details Обрабатывает нажатие кнопки выбора типа входных данных.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderDataType_clicked() {
    resetEncoderNS();
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderDataType_1) {
        ui->horizontalSliderDataType_2->setValue(0);
        if(senderSlider->value() == 0) {
            encodeTypeFlag = NUMERIC;
            setEnabledNS(true);
        } else {
            encodeTypeFlag = NO_TYPE;
            setEnabledNS(false);
        }
    } else if (senderSlider == ui->horizontalSliderDataType_2) {
        ui->horizontalSliderDataType_1->setValue(0);
        if(senderSlider->value() == 0) {
            encodeTypeFlag = TEXT;
            setEnabledNS(false);
        } else {
            encodeTypeFlag = NO_TYPE;
            setEnabledNS(false);
        }
    }
    bool enableFrame = senderSlider != ui->horizontalSliderDataType_2 ||
                       (senderSlider->value() == 1);
    if (enableFrame) {
        removeEffect(ui->frame_5);
        setShadow(ui->frame_5);
        removeEffect(ui->frame_11);
    } else {
        setBlur(ui->frame_5, BLUR_RADIUS_1);
        setBlur(ui->frame_11, BLUR_RADIUS_2);
    }
    ui->horizontalSliderEncoder1511d->setEnabled(enableFrame);
    ui->frame_5->update();
    ui->frame_11->update();
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор системы счисления" при кодировании.
 * \details Обрабатывает нажатие кнопки выбора системы счисления.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderNS_clicked() {
    resetAlgo();
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    QList<QSlider*> sliders = { ui->horizontalSliderNS2,
                                ui->horizontalSliderNS4,
                                ui->horizontalSliderNS8,
                                ui->horizontalSliderNS10,
                                ui->horizontalSliderNS16, };
    for (QSlider *slider : sliders) {
        if (slider != senderSlider) {
            slider->setValue(0);
        }
    }
    if (senderSlider->value() == 0) {
        if (senderSlider == ui->horizontalSliderNS2)
            encodeNumberFlag = BINARY;
        else if (senderSlider == ui->horizontalSliderNS4)
            encodeNumberFlag = QUATERNARY;
        else if (senderSlider == ui->horizontalSliderNS8)
            encodeNumberFlag = OCTAL;
        else if (senderSlider == ui->horizontalSliderNS10)
            encodeNumberFlag = DECIMAL;
        else if (senderSlider == ui->horizontalSliderNS16)
            encodeNumberFlag = HEXADECIMAL;
    } else {
        encodeNumberFlag = NO_SYSTEM;
    }
    bool enableFrame = senderSlider == ui->horizontalSliderNS10 || senderSlider->value() == 1;
    ui->horizontalSliderEncoder1511d->setEnabled(enableFrame);
    if(enableFrame) {
        removeEffect(ui->frame_11);
    } else {
        setBlur(ui->frame_11, BLUR_RADIUS_1);
    }
    ui->frame_11->update();
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор алгоритма кодирования".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderEncoder_clicked() {
    resetEncoderData();
    QSlider *senderSlider = qobject_cast<QSlider*>(sender());
    QList<QSlider*> sliders = { ui->horizontalSliderEncoder74,
                                ui->horizontalSliderEncoder84,
                                ui->horizontalSliderEncoder1511,
                                ui->horizontalSliderEncoder1611,
                                ui->horizontalSliderEncoder1511d, };
    for (QSlider *slider : sliders) {
        if(slider != senderSlider) {
            slider->setValue(0);
        }
    }
    if (!senderSlider->value()) {
        if(senderSlider == ui->horizontalSliderEncoder74) {
            encodeAlgFlag = ALG_74;
        } else if(senderSlider == ui->horizontalSliderEncoder84) {
            encodeAlgFlag = ALG_84;
        } else if(senderSlider == ui->horizontalSliderEncoder1511) {
            encodeAlgFlag = ALG_1511;
        } else if(senderSlider == ui->horizontalSliderEncoder1611) {
            encodeAlgFlag = ALG_1611;
        } else if(senderSlider == ui->horizontalSliderEncoder1511d) {
            encodeAlgFlag = ALG_1511d;
        }
        ui->stackedWidget_2->setCurrentIndex(encodeAlgFlag);
        ui->stackedWidget_3->setCurrentIndex(encodeAlgFlag);
        ui->stackedWidget_4->setCurrentIndex(encodeAlgFlag);
        if (encodeAlgFlag == ALG_74 || encodeAlgFlag == ALG_84) {
            ui->stackedWidget_5->setCurrentIndex(0);
        } else if(encodeAlgFlag != NO_ALG) {
            ui->stackedWidget_5->setCurrentIndex(1);
        }
    } else {
        encodeAlgFlag = NO_ALG;
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Автоматическая генерация".
 * \details Обрабатывает нажатие кнопки автоматической генерации.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonAutoGen_clicked() {
    switch (encodeTypeFlag) {
    case NO_TYPE: {
        NotificationForm *notification = new NotificationForm("Генерация невозможна. Выберите тип данных.");
        this->setEnabled(false);
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, this, [=]() {
            notification->deleteLater();
            this->setEnabled(true);
        });
        break;
    }
    case TEXT: {
        ui->textEditData->setText(NumberGenerator::generate(ui->spinBoxAmount->value()));
        break;
    }
    case NUMERIC: {
        switch(encodeNumberFlag) {
        case NO_SYSTEM: {
            NotificationForm *notification = new NotificationForm("Генерация невозможна. Выберите систему счисления.");
            this->setEnabled(false);
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                notification->deleteLater();
                this->setEnabled(true);
            });
            break;
        }
        case BINARY: {
            ui->textEditData->setText(NumberGenerator::generate(BINARY, ui->spinBoxAmount->value()));
            break;
        }
        case QUATERNARY: {
            ui->textEditData->setText(NumberGenerator::generate(QUATERNARY, ui->spinBoxAmount->value()));
            break;
        }
        case OCTAL: {
            ui->textEditData->setText(NumberGenerator::generate(OCTAL, ui->spinBoxAmount->value()));
            break;
        }
        case DECIMAL: {
            ui->textEditData->setText(NumberGenerator::generate(DECIMAL, ui->spinBoxAmount->value()));
            break;
        }
        case HEXADECIMAL: {
            ui->textEditData->setText(NumberGenerator::generate(HEXADECIMAL, ui->spinBoxAmount->value()));
            break;
        }
        }
        break;
    }
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Кодирование".
 * \details Обрабатывает нажатие кнопки кодирования.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonEncode_clicked() {
    if(encodeTypeFlag == NO_TYPE) {
        NotificationForm *notification = new NotificationForm("Кодирование невозможна. Выберите тип данных.");
        this->setEnabled(false);
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, this, [=]() {
            notification->deleteLater();
            this->setEnabled(true);
        });
    } else {
        QString data = ui->textEditData->toPlainText();
        bool dataFlag = false;
        if(encodeTypeFlag == TEXT) {
            dataFlag = true;
            Converter::toBinary(bitSeq, data);
        } else {
            Converter::toBinary(bitSeq, data, encodeNumberFlag);
            switch (encodeNumberFlag) {
            case NO_SYSTEM: {
                break;
            }
            case BINARY: {
                dataFlag = BINARY_REGEX.match(data).hasMatch();
                break;
            }
            case QUATERNARY: {
                dataFlag = QUATERNARY_REGEX.match(data).hasMatch();
                break;
            }
            case OCTAL: {
                dataFlag = OCTAL_REGEX.match(data).hasMatch();
                break;
            }
            case DECIMAL: {
                dataFlag = DECIMAL_REGEX.match(data).hasMatch();
                break;
            }
            case HEXADECIMAL: {
                dataFlag = HEXADECIMAL_REGEX.match(data).hasMatch();
                break;
            }
            }
        }
        if(dataFlag) {
            switch (encodeAlgFlag) {
            case NO_ALG: {
                NotificationForm *notification = new NotificationForm("Кодирование невозможно. "
                                                                      "Выберите алгоритм.");
                this->setEnabled(false);
                notification->show();
                QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                    notification->deleteLater();
                    this->setEnabled(true);
                });
                break;
            }
            case ALG_74: {
                setListSeq(4, bitSeq, ui->listWidget);
                setListSeq(4, bitSeq, ui->listWidget_2);
                clearEncodedBitSeq = Encoder74::start(bitSeq);
                modEncodedBitSeq = clearEncodedBitSeq;
                break;
            }
            case ALG_84: {
                setListSeq(4, bitSeq, ui->listWidget);
                setListSeq(4, bitSeq, ui->listWidget_2);
                clearEncodedBitSeq = Encoder84::start(bitSeq);
                modEncodedBitSeq = clearEncodedBitSeq;
                break;
            }
            case ALG_1511: {
                setListSeq(11, bitSeq, ui->listWidget);
                setListSeq(11, bitSeq, ui->listWidget_2);
                clearEncodedBitSeq = Encoder1511::start(bitSeq);
                modEncodedBitSeq = clearEncodedBitSeq;
                break;
            }
            case ALG_1611: {
                setListSeq(11, bitSeq, ui->listWidget);
                setListSeq(11, bitSeq, ui->listWidget_2);
                clearEncodedBitSeq = Encoder1611::start(bitSeq);
                modEncodedBitSeq = clearEncodedBitSeq;
                break;
            }
            case ALG_1511d: {
                bigInt = BigInteger(data);
                setListInt(11, bigInt, ui->listWidget);
                setListInt(11, bigInt, ui->listWidget_2);
                clearEncodedBigInt = EncoderDecimal1511::start(bigInt);
                modEncodedBigInt = clearEncodedBigInt;
                break;
            }
            }
        } else {
            NotificationForm *notification = new NotificationForm("Система счисления была выбрана неверно. "
                                                                  "Вам следует проверить входные данные");
            this->setEnabled(false);
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                notification->deleteLater();
                this->setEnabled(true);
            });
        }
    }
}


/*!
 * \brief Метод для установки содержимого списка с последовательностями бит.
 * \param size Длина битовых подпоследовательностей.
 * \param data Исходная битовая последовательность.
 * \return Отсутствуют.
*/
void StudyForm::setListSeq(const int &size, const BitSequence &data, QListWidget *listWidget) {
    listWidget->clear();
    int eSize = data.length();
    if (eSize % size) {
        eSize += size - (eSize % size);
    }
    for(int i = eSize; i > 0; i -= size) {
        listWidget->addItem(data.subsequence(i - size, i - 1).toString());
    }
}


/*!
 * \brief Метод для установки содержимого списка с натуральными числами.
 * \param size Длина фрагмента.
 * \param data Исходное число.
 * \return Отсутствуют.
*/
void StudyForm::setListInt(const int &size, const BigInteger &data, QListWidget *listWidget) {
    listWidget->clear();
    int eSize = data.length();
    if(eSize % size) {
        eSize += size - (eSize % size);
    }
    for(int i = eSize; i > 0; i -= size) {
        listWidget->addItem(data.subdigit(i - size, i - 1).toString());
    }
}


/*!
 * \brief Метод для установки содержимого ячеек значений для вкладки "Кодирование".
 * \param size Длина битовой последовательности.
 * \return Отсутствуют.
*/
void StudyForm::setBitsEncoding(const int &index) {
    QString data, encodedData;
    if(encodeAlgFlag != ALG_1511d) {
        data = clearEncodedBitSeq[index].first.toString();
        encodedData = clearEncodedBitSeq[index].second.toString();
        switch (encodeAlgFlag) {
        case NO_ALG: {
            break;
        }
        case ALG_74: {
            /// \brief Установка значений во вкладке "Кодирование"
            ui->labelX_id_74_4->setText(data.at(0));
            ui->labelX_id_74_3->setText(data.at(1));
            ui->labelX_id_74_2->setText(data.at(2));
            ui->labelX_id_74_1->setText(data.at(3));
            ui->labelY_od_74_7->setText(encodedData.at(0));
            ui->labelY_od_74_6->setText(encodedData.at(1));
            ui->labelY_od_74_5->setText(encodedData.at(2));
            ui->labelY_od_74_4->setText(encodedData.at(3));
            ui->labelY_od_74_3->setText(encodedData.at(4));
            ui->labelY_od_74_2->setText(encodedData.at(5));
            ui->labelY_od_74_1->setText(encodedData.at(6));
            break;
        }
        case ALG_84: {
            /// \brief Установка значений во вкладке "Кодирование"
            ui->labelX_id_84_4->setText(data.at(0));
            ui->labelX_id_84_3->setText(data.at(1));
            ui->labelX_id_84_2->setText(data.at(2));
            ui->labelX_id_84_1->setText(data.at(3));
            ui->labelY_od_84_8->setText(encodedData.at(0));
            ui->labelY_od_84_7->setText(encodedData.at(1));
            ui->labelY_od_84_6->setText(encodedData.at(2));
            ui->labelY_od_84_5->setText(encodedData.at(3));
            ui->labelY_od_84_4->setText(encodedData.at(4));
            ui->labelY_od_84_3->setText(encodedData.at(5));
            ui->labelY_od_84_2->setText(encodedData.at(6));
            ui->labelY_od_84_1->setText(encodedData.at(7));
            break;
        }
        case ALG_1511: {
            /// \brief Установка значений во вкладке "Кодирование"
            ui->labelX_id_1511_11->setText(data.at(0));
            ui->labelX_id_1511_10->setText(data.at(1));
            ui->labelX_id_1511_9->setText(data.at(2));
            ui->labelX_id_1511_8->setText(data.at(3));
            ui->labelX_id_1511_7->setText(data.at(4));
            ui->labelX_id_1511_6->setText(data.at(5));
            ui->labelX_id_1511_5->setText(data.at(6));
            ui->labelX_id_1511_4->setText(data.at(7));
            ui->labelX_id_1511_3->setText(data.at(8));
            ui->labelX_id_1511_2->setText(data.at(9));
            ui->labelX_id_1511_1->setText(data.at(10));
            ui->labelY_id_1511_15->setText(encodedData.at(0));
            ui->labelY_id_1511_14->setText(encodedData.at(1));
            ui->labelY_id_1511_13->setText(encodedData.at(2));
            ui->labelY_id_1511_12->setText(encodedData.at(3));
            ui->labelY_id_1511_11->setText(encodedData.at(4));
            ui->labelY_id_1511_10->setText(encodedData.at(5));
            ui->labelY_id_1511_9->setText(encodedData.at(6));
            ui->labelY_id_1511_8->setText(encodedData.at(7));
            ui->labelY_id_1511_7->setText(encodedData.at(8));
            ui->labelY_id_1511_6->setText(encodedData.at(9));
            ui->labelY_id_1511_5->setText(encodedData.at(10));
            ui->labelY_id_1511_4->setText(encodedData.at(11));
            ui->labelY_id_1511_3->setText(encodedData.at(12));
            ui->labelY_id_1511_2->setText(encodedData.at(13));
            ui->labelY_id_1511_1->setText(encodedData.at(14));
            break;
        }
        case ALG_1611: {
            /// \brief Установка значений во вкладке "Кодирование"
            ui->labelX_id_1611_11->setText(data.at(0));
            ui->labelX_id_1611_10->setText(data.at(1));
            ui->labelX_id_1611_9->setText(data.at(2));
            ui->labelX_id_1611_8->setText(data.at(3));
            ui->labelX_id_1611_7->setText(data.at(3));
            ui->labelX_id_1611_6->setText(data.at(3));
            ui->labelX_id_1611_5->setText(data.at(3));
            ui->labelX_id_1611_4->setText(data.at(3));
            ui->labelX_id_1611_3->setText(data.at(3));
            ui->labelX_id_1611_2->setText(data.at(3));
            ui->labelX_id_1611_1->setText(data.at(3));
            ui->labelY_id_1611_16->setText(encodedData.at(0));
            ui->labelY_id_1611_15->setText(encodedData.at(1));
            ui->labelY_id_1611_14->setText(encodedData.at(2));
            ui->labelY_id_1611_13->setText(encodedData.at(3));
            ui->labelY_id_1611_12->setText(encodedData.at(4));
            ui->labelY_id_1611_11->setText(encodedData.at(5));
            ui->labelY_id_1611_10->setText(encodedData.at(6));
            ui->labelY_id_1611_9->setText(encodedData.at(7));
            ui->labelY_id_1611_8->setText(encodedData.at(8));
            ui->labelY_id_1611_7->setText(encodedData.at(9));
            ui->labelY_id_1611_6->setText(encodedData.at(10));
            ui->labelY_id_1611_5->setText(encodedData.at(11));
            ui->labelY_id_1611_4->setText(encodedData.at(12));
            ui->labelY_id_1611_3->setText(encodedData.at(13));
            ui->labelY_id_1611_2->setText(encodedData.at(14));
            ui->labelY_id_1611_1->setText(encodedData.at(15));
            break;
        }
        default: {
            break;
        }
        }
    } else {
        /// \brief Установка значений во вкладке "Кодирование"
        data = clearEncodedBigInt[index].first.toString();
        encodedData = clearEncodedBigInt[index].second.toString();
        ui->labelX_id_d1511_11->setText(data.at(0));
        ui->labelX_id_d1511_10->setText(data.at(1));
        ui->labelX_id_d1511_9->setText(data.at(2));
        ui->labelX_id_d1511_8->setText(data.at(3));
        ui->labelX_id_d1511_7->setText(data.at(4));
        ui->labelX_id_d1511_6->setText(data.at(5));
        ui->labelX_id_d1511_5->setText(data.at(6));
        ui->labelX_id_d1511_4->setText(data.at(7));
        ui->labelX_id_d1511_3->setText(data.at(8));
        ui->labelX_id_d1511_2->setText(data.at(9));
        ui->labelX_id_d1511_1->setText(data.at(10));
        ui->labelY_id_d1511_15->setText(encodedData.at(0));
        ui->labelY_id_d1511_14->setText(encodedData.at(1));
        ui->labelY_id_d1511_13->setText(encodedData.at(2));
        ui->labelY_id_d1511_12->setText(encodedData.at(3));
        ui->labelY_id_d1511_11->setText(encodedData.at(4));
        ui->labelY_id_d1511_10->setText(encodedData.at(5));
        ui->labelY_id_d1511_9->setText(encodedData.at(6));
        ui->labelY_id_d1511_8->setText(encodedData.at(7));
        ui->labelY_id_d1511_7->setText(encodedData.at(8));
        ui->labelY_id_d1511_6->setText(encodedData.at(9));
        ui->labelY_id_d1511_5->setText(encodedData.at(10));
        ui->labelY_id_d1511_4->setText(encodedData.at(11));
        ui->labelY_id_d1511_3->setText(encodedData.at(12));
        ui->labelY_id_d1511_2->setText(encodedData.at(13));
        ui->labelY_id_d1511_1->setText(encodedData.at(14));
    }
}


/*!
 * \brief Метод для установки содержимого ячеек значений для вкладки "Шум".
 * \param size Длина битовой последовательности.
 * \return Отсутствуют.
*/
void StudyForm::setBitsNoise(const int &index, const bool &onlyMode) {
    QString data, encodedData, modData;
    if(encodeAlgFlag != ALG_1511d) {
        data = clearEncodedBitSeq[index].first.toString();
        encodedData = clearEncodedBitSeq[index].second.toString();
        modData = modEncodedBitSeq[index].second.toString();
        switch (encodeAlgFlag) {
        case NO_ALG: {
            break;
        }
        case ALG_74: {
            /// \brief Установка значений во вкладке "Шум"
            if(!onlyMode) {
                ui->labelY_id_74_2_7->setText(encodedData.at(0));
                ui->labelY_id_74_2_6->setText(encodedData.at(1));
                ui->labelY_id_74_2_5->setText(encodedData.at(2));
                ui->labelY_id_74_2_4->setText(encodedData.at(3));
                ui->labelY_id_74_2_3->setText(encodedData.at(4));
                ui->labelY_id_74_2_2->setText(encodedData.at(5));
                ui->labelY_id_74_2_1->setText(encodedData.at(6));
            }
            ui->labelY_od_74_2_7->setText(modData.at(0));
            ui->labelY_od_74_2_6->setText(modData.at(1));
            ui->labelY_od_74_2_5->setText(modData.at(2));
            ui->labelY_od_74_2_4->setText(modData.at(3));
            ui->labelY_od_74_2_3->setText(modData.at(4));
            ui->labelY_od_74_2_2->setText(modData.at(5));
            ui->labelY_od_74_2_1->setText(modData.at(6));
            break;
        }
        case ALG_84: {
            if(!onlyMode) {
                ui->labelY_id_84_2_8->setText(encodedData.at(0));
                ui->labelY_id_84_2_7->setText(encodedData.at(1));
                ui->labelY_id_84_2_6->setText(encodedData.at(2));
                ui->labelY_id_84_2_5->setText(encodedData.at(3));
                ui->labelY_id_84_2_4->setText(encodedData.at(4));
                ui->labelY_id_84_2_3->setText(encodedData.at(5));
                ui->labelY_id_84_2_2->setText(encodedData.at(6));
                ui->labelY_id_84_2_1->setText(encodedData.at(7));
            }
            ui->labelY_od_84_2_8->setText(modData.at(0));
            ui->labelY_od_84_2_7->setText(modData.at(1));
            ui->labelY_od_84_2_6->setText(modData.at(2));
            ui->labelY_od_84_2_5->setText(modData.at(3));
            ui->labelY_od_84_2_4->setText(modData.at(4));
            ui->labelY_od_84_2_3->setText(modData.at(5));
            ui->labelY_od_84_2_2->setText(modData.at(6));
            ui->labelY_od_84_2_1->setText(modData.at(7));
            break;
        }
        case ALG_1511: {
            if(!onlyMode) {
                ui->labelY_id_1511_2_15->setText(encodedData.at(0));
                ui->labelY_id_1511_2_14->setText(encodedData.at(1));
                ui->labelY_id_1511_2_13->setText(encodedData.at(2));
                ui->labelY_id_1511_2_12->setText(encodedData.at(3));
                ui->labelY_id_1511_2_11->setText(encodedData.at(4));
                ui->labelY_id_1511_2_10->setText(encodedData.at(5));
                ui->labelY_id_1511_2_9->setText(encodedData.at(6));
                ui->labelY_id_1511_2_8->setText(encodedData.at(7));
                ui->labelY_id_1511_2_7->setText(encodedData.at(8));
                ui->labelY_id_1511_2_6->setText(encodedData.at(9));
                ui->labelY_id_1511_2_5->setText(encodedData.at(10));
                ui->labelY_id_1511_2_4->setText(encodedData.at(11));
                ui->labelY_id_1511_2_3->setText(encodedData.at(12));
                ui->labelY_id_1511_2_2->setText(encodedData.at(13));
                ui->labelY_id_1511_2_1->setText(encodedData.at(14));
            }
            ui->labelY_od_1511_2_15->setText(modData.at(0));
            ui->labelY_od_1511_2_14->setText(modData.at(1));
            ui->labelY_od_1511_2_13->setText(modData.at(2));
            ui->labelY_od_1511_2_12->setText(modData.at(3));
            ui->labelY_od_1511_2_11->setText(modData.at(4));
            ui->labelY_od_1511_2_10->setText(modData.at(5));
            ui->labelY_od_1511_2_9->setText(modData.at(6));
            ui->labelY_od_1511_2_8->setText(modData.at(7));
            ui->labelY_od_1511_2_7->setText(modData.at(8));
            ui->labelY_od_1511_2_6->setText(modData.at(9));
            ui->labelY_od_1511_2_5->setText(modData.at(10));
            ui->labelY_od_1511_2_4->setText(modData.at(11));
            ui->labelY_od_1511_2_3->setText(modData.at(12));
            ui->labelY_od_1511_2_2->setText(modData.at(13));
            ui->labelY_od_1511_2_1->setText(modData.at(14));
            break;
        }
        case ALG_1611: {
            if(!onlyMode) {
                ui->labelY_id_1611_2_16->setText(encodedData.at(0));
                ui->labelY_id_1611_2_15->setText(encodedData.at(1));
                ui->labelY_id_1611_2_14->setText(encodedData.at(2));
                ui->labelY_id_1611_2_13->setText(encodedData.at(3));
                ui->labelY_id_1611_2_12->setText(encodedData.at(4));
                ui->labelY_id_1611_2_11->setText(encodedData.at(5));
                ui->labelY_id_1611_2_10->setText(encodedData.at(6));
                ui->labelY_id_1611_2_9->setText(encodedData.at(7));
                ui->labelY_id_1611_2_8->setText(encodedData.at(8));
                ui->labelY_id_1611_2_7->setText(encodedData.at(9));
                ui->labelY_id_1611_2_6->setText(encodedData.at(10));
                ui->labelY_id_1611_2_5->setText(encodedData.at(11));
                ui->labelY_id_1611_2_4->setText(encodedData.at(12));
                ui->labelY_id_1611_2_3->setText(encodedData.at(13));
                ui->labelY_id_1611_2_2->setText(encodedData.at(14));
                ui->labelY_id_1611_2_1->setText(encodedData.at(15));
            }
            ui->labelY_od_1611_2_16->setText(modData.at(0));
            ui->labelY_od_1611_2_15->setText(modData.at(1));
            ui->labelY_od_1611_2_14->setText(modData.at(2));
            ui->labelY_od_1611_2_13->setText(modData.at(3));
            ui->labelY_od_1611_2_12->setText(modData.at(4));
            ui->labelY_od_1611_2_11->setText(modData.at(5));
            ui->labelY_od_1611_2_10->setText(modData.at(6));
            ui->labelY_od_1611_2_9->setText(modData.at(7));
            ui->labelY_od_1611_2_8->setText(modData.at(8));
            ui->labelY_od_1611_2_7->setText(modData.at(9));
            ui->labelY_od_1611_2_6->setText(modData.at(10));
            ui->labelY_od_1611_2_5->setText(modData.at(11));
            ui->labelY_od_1611_2_4->setText(modData.at(12));
            ui->labelY_od_1611_2_3->setText(modData.at(13));
            ui->labelY_od_1611_2_2->setText(modData.at(14));
            ui->labelY_od_1611_2_1->setText(modData.at(15));
            break;
        }
        default: {
            break;
        }
        }
    } else {
        data = clearEncodedBigInt[index].first.toString();
        encodedData = clearEncodedBigInt[index].second.toString();
        modData = modEncodedBigInt[index].second.toString();
        if(!onlyMode) {
            ui->labelY_id_d1511_2_15->setText(encodedData.at(0));
            ui->labelY_id_d1511_2_14->setText(encodedData.at(1));
            ui->labelY_id_d1511_2_13->setText(encodedData.at(2));
            ui->labelY_id_d1511_2_12->setText(encodedData.at(3));
            ui->labelY_id_d1511_2_11->setText(encodedData.at(4));
            ui->labelY_id_d1511_2_10->setText(encodedData.at(5));
            ui->labelY_id_d1511_2_9->setText(encodedData.at(6));
            ui->labelY_id_d1511_2_8->setText(encodedData.at(7));
            ui->labelY_id_d1511_2_7->setText(encodedData.at(8));
            ui->labelY_id_d1511_2_6->setText(encodedData.at(9));
            ui->labelY_id_d1511_2_5->setText(encodedData.at(10));
            ui->labelY_id_d1511_2_4->setText(encodedData.at(11));
            ui->labelY_id_d1511_2_3->setText(encodedData.at(12));
            ui->labelY_id_d1511_2_2->setText(encodedData.at(13));
            ui->labelY_id_d1511_2_1->setText(encodedData.at(14));
        }
        ui->labelY_od_d1511_2_15->setText(modData.at(0));
        ui->labelY_od_d1511_2_14->setText(modData.at(1));
        ui->labelY_od_d1511_2_13->setText(modData.at(2));
        ui->labelY_od_d1511_2_12->setText(modData.at(3));
        ui->labelY_od_d1511_2_11->setText(modData.at(4));
        ui->labelY_od_d1511_2_10->setText(modData.at(5));
        ui->labelY_od_d1511_2_9->setText(modData.at(6));
        ui->labelY_od_d1511_2_8->setText(modData.at(7));
        ui->labelY_od_d1511_2_7->setText(modData.at(8));
        ui->labelY_od_d1511_2_6->setText(modData.at(9));
        ui->labelY_od_d1511_2_5->setText(modData.at(10));
        ui->labelY_od_d1511_2_4->setText(modData.at(11));
        ui->labelY_od_d1511_2_3->setText(modData.at(12));
        ui->labelY_od_d1511_2_2->setText(modData.at(13));
        ui->labelY_od_d1511_2_1->setText(modData.at(14));
    }
    if(!onlyMode) {
        if (encodeAlgFlag == ALG_74 || encodeAlgFlag == ALG_84) {
            ui->labelX_d_74_2_4->setText(data.at(0));
            ui->labelX_d_74_2_3->setText(data.at(1));
            ui->labelX_d_74_2_2->setText(data.at(2));
            ui->labelX_d_74_2_1->setText(data.at(3));
        } else if (encodeAlgFlag != NO_ALG) {
            ui->labelX_d_1511_2_11->setText(data.at(0));
            ui->labelX_d_1511_2_10->setText(data.at(1));
            ui->labelX_d_1511_2_9->setText(data.at(2));
            ui->labelX_d_1511_2_8->setText(data.at(3));
            ui->labelX_d_1511_2_7->setText(data.at(4));
            ui->labelX_d_1511_2_6->setText(data.at(5));
            ui->labelX_d_1511_2_5->setText(data.at(6));
            ui->labelX_d_1511_2_4->setText(data.at(7));
            ui->labelX_d_1511_2_3->setText(data.at(8));
            ui->labelX_d_1511_2_2->setText(data.at(9));
            ui->labelX_d_1511_2_1->setText(data.at(10));
        }
    }
}


/*!
 * \brief Метод для сброса выбранного алгоритма кодирования.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetAlgo() {
    ui->horizontalSliderEncoder74->setValue(0);
    ui->horizontalSliderEncoder84->setValue(0);
    ui->horizontalSliderEncoder1511->setValue(0);
    ui->horizontalSliderEncoder1611->setValue(0);
    ui->horizontalSliderEncoder1511d->setValue(0);
    encodeAlgFlag = NO_ALG;
}


/*!
 * \brief Метод для сброса выбранного алгоритма.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetEncoderNS() {
    ui->horizontalSliderNS2->setValue(0);
    ui->horizontalSliderNS4->setValue(0);
    ui->horizontalSliderNS8->setValue(0);
    ui->horizontalSliderNS10->setValue(0);
    ui->horizontalSliderNS16->setValue(0);
    encodeNumberFlag = NO_SYSTEM;
}


/*!
 * \brief Метод для включения/выключения выбора алгоритмов при кодировании.
 * \param Flag Включение/выключение.
 * \return Отсутствуют.
*/
void StudyForm::setEnabledNS(const bool &flag) {
    ui->horizontalSliderNS2->setEnabled(flag);
    ui->horizontalSliderNS4->setEnabled(flag);
    ui->horizontalSliderNS8->setEnabled(flag);
    ui->horizontalSliderNS10->setEnabled(flag);
    ui->horizontalSliderNS16->setEnabled(flag);
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 7-4.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageEncoder74() {
    ui->labelX_id_74_4->clear();
    ui->labelX_id_74_3->clear();
    ui->labelX_id_74_2->clear();
    ui->labelX_id_74_1->clear();
    ui->labelY_od_74_7->clear();
    ui->labelY_od_74_6->clear();
    ui->labelY_od_74_5->clear();
    ui->labelY_od_74_4->clear();
    ui->labelY_od_74_3->clear();
    ui->labelY_od_74_2->clear();
    ui->labelY_od_74_1->clear();
    ui->labelY_id_74_2_7->clear();
    ui->labelY_id_74_2_6->clear();
    ui->labelY_id_74_2_5->clear();
    ui->labelY_id_74_2_4->clear();
    ui->labelY_id_74_2_3->clear();
    ui->labelY_id_74_2_2->clear();
    ui->labelY_id_74_2_1->clear();
    ui->labelY_od_74_2_7->clear();
    ui->labelY_od_74_2_6->clear();
    ui->labelY_od_74_2_5->clear();
    ui->labelY_od_74_2_4->clear();
    ui->labelY_od_74_2_3->clear();
    ui->labelY_od_74_2_2->clear();
    ui->labelY_od_74_2_1->clear();
    resetLabelXd4();
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 8-4.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageEncoder84() {
    ui->labelX_id_84_4->clear();
    ui->labelX_id_84_3->clear();
    ui->labelX_id_84_2->clear();
    ui->labelX_id_84_1->clear();
    ui->labelY_od_84_8->clear();
    ui->labelY_od_84_7->clear();
    ui->labelY_od_84_6->clear();
    ui->labelY_od_84_5->clear();
    ui->labelY_od_84_4->clear();
    ui->labelY_od_84_3->clear();
    ui->labelY_od_84_2->clear();
    ui->labelY_od_84_1->clear();
    ui->labelY_id_84_2_8->clear();
    ui->labelY_id_84_2_7->clear();
    ui->labelY_id_84_2_6->clear();
    ui->labelY_id_84_2_5->clear();
    ui->labelY_id_84_2_4->clear();
    ui->labelY_id_84_2_3->clear();
    ui->labelY_id_84_2_2->clear();
    ui->labelY_id_84_2_1->clear();
    ui->labelY_od_84_2_8->clear();
    ui->labelY_od_84_2_7->clear();
    ui->labelY_od_84_2_6->clear();
    ui->labelY_od_84_2_5->clear();
    ui->labelY_od_84_2_4->clear();
    ui->labelY_od_84_2_3->clear();
    ui->labelY_od_84_2_2->clear();
    ui->labelY_od_84_2_1->clear();
    resetLabelXd4();
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 15-11.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageEncoder1511() {
    ui->labelX_id_1511_11->clear();
    ui->labelX_id_1511_10->clear();
    ui->labelX_id_1511_9->clear();
    ui->labelX_id_1511_8->clear();
    ui->labelX_id_1511_7->clear();
    ui->labelX_id_1511_6->clear();
    ui->labelX_id_1511_5->clear();
    ui->labelX_id_1511_4->clear();
    ui->labelX_id_1511_3->clear();
    ui->labelX_id_1511_2->clear();
    ui->labelX_id_1511_1->clear();
    ui->labelY_id_1511_15->clear();
    ui->labelY_id_1511_14->clear();
    ui->labelY_id_1511_13->clear();
    ui->labelY_id_1511_12->clear();
    ui->labelY_id_1511_11->clear();
    ui->labelY_id_1511_10->clear();
    ui->labelY_id_1511_9->clear();
    ui->labelY_id_1511_8->clear();
    ui->labelY_id_1511_7->clear();
    ui->labelY_id_1511_6->clear();
    ui->labelY_id_1511_5->clear();
    ui->labelY_id_1511_4->clear();
    ui->labelY_id_1511_3->clear();
    ui->labelY_id_1511_2->clear();
    ui->labelY_id_1511_1->clear();
    ui->labelY_id_1511_2_15->clear();
    ui->labelY_id_1511_2_14->clear();
    ui->labelY_id_1511_2_13->clear();
    ui->labelY_id_1511_2_12->clear();
    ui->labelY_id_1511_2_11->clear();
    ui->labelY_id_1511_2_10->clear();
    ui->labelY_id_1511_2_9->clear();
    ui->labelY_id_1511_2_8->clear();
    ui->labelY_id_1511_2_7->clear();
    ui->labelY_id_1511_2_6->clear();
    ui->labelY_id_1511_2_5->clear();
    ui->labelY_id_1511_2_4->clear();
    ui->labelY_id_1511_2_3->clear();
    ui->labelY_id_1511_2_2->clear();
    ui->labelY_id_1511_2_1->clear();
    ui->labelY_od_1511_2_15->clear();
    ui->labelY_od_1511_2_14->clear();
    ui->labelY_od_1511_2_13->clear();
    ui->labelY_od_1511_2_12->clear();
    ui->labelY_od_1511_2_11->clear();
    ui->labelY_od_1511_2_10->clear();
    ui->labelY_od_1511_2_9->clear();
    ui->labelY_od_1511_2_8->clear();
    ui->labelY_od_1511_2_7->clear();
    ui->labelY_od_1511_2_6->clear();
    ui->labelY_od_1511_2_5->clear();
    ui->labelY_od_1511_2_4->clear();
    ui->labelY_od_1511_2_3->clear();
    ui->labelY_od_1511_2_2->clear();
    ui->labelY_od_1511_2_1->clear();
    resetLabelXd11();
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 16-11.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageEncoder1611() {
    ui->labelX_id_1611_11->clear();
    ui->labelX_id_1611_10->clear();
    ui->labelX_id_1611_9->clear();
    ui->labelX_id_1611_8->clear();
    ui->labelX_id_1611_7->clear();
    ui->labelX_id_1611_6->clear();
    ui->labelX_id_1611_5->clear();
    ui->labelX_id_1611_4->clear();
    ui->labelX_id_1611_3->clear();
    ui->labelX_id_1611_2->clear();
    ui->labelX_id_1611_1->clear();
    ui->labelY_id_1611_16->clear();
    ui->labelY_id_1611_15->clear();
    ui->labelY_id_1611_14->clear();
    ui->labelY_id_1611_13->clear();
    ui->labelY_id_1611_12->clear();
    ui->labelY_id_1611_11->clear();
    ui->labelY_id_1611_10->clear();
    ui->labelY_id_1611_9->clear();
    ui->labelY_id_1611_8->clear();
    ui->labelY_id_1611_7->clear();
    ui->labelY_id_1611_6->clear();
    ui->labelY_id_1611_5->clear();
    ui->labelY_id_1611_4->clear();
    ui->labelY_id_1611_3->clear();
    ui->labelY_id_1611_2->clear();
    ui->labelY_id_1611_1->clear();
    ui->labelY_id_1611_2_16->clear();
    ui->labelY_id_1611_2_15->clear();
    ui->labelY_id_1611_2_14->clear();
    ui->labelY_id_1611_2_13->clear();
    ui->labelY_id_1611_2_12->clear();
    ui->labelY_id_1611_2_11->clear();
    ui->labelY_id_1611_2_10->clear();
    ui->labelY_id_1611_2_9->clear();
    ui->labelY_id_1611_2_8->clear();
    ui->labelY_id_1611_2_7->clear();
    ui->labelY_id_1611_2_6->clear();
    ui->labelY_id_1611_2_5->clear();
    ui->labelY_id_1611_2_4->clear();
    ui->labelY_id_1611_2_3->clear();
    ui->labelY_id_1611_2_2->clear();
    ui->labelY_id_1611_2_1->clear();
    ui->labelY_od_1611_2_16->clear();
    ui->labelY_od_1611_2_15->clear();
    ui->labelY_od_1611_2_14->clear();
    ui->labelY_od_1611_2_13->clear();
    ui->labelY_od_1611_2_12->clear();
    ui->labelY_od_1611_2_11->clear();
    ui->labelY_od_1611_2_10->clear();
    ui->labelY_od_1611_2_9->clear();
    ui->labelY_od_1611_2_8->clear();
    ui->labelY_od_1611_2_7->clear();
    ui->labelY_od_1611_2_6->clear();
    ui->labelY_od_1611_2_5->clear();
    ui->labelY_od_1611_2_4->clear();
    ui->labelY_od_1611_2_3->clear();
    ui->labelY_od_1611_2_2->clear();
    ui->labelY_od_1611_2_1->clear();
    resetLabelXd11();
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 15-11d.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageEncoder1511d() {
    ui->labelX_id_d1511_11->clear();
    ui->labelX_id_d1511_10->clear();
    ui->labelX_id_d1511_9->clear();
    ui->labelX_id_d1511_8->clear();
    ui->labelX_id_d1511_7->clear();
    ui->labelX_id_d1511_6->clear();
    ui->labelX_id_d1511_5->clear();
    ui->labelX_id_d1511_4->clear();
    ui->labelX_id_d1511_3->clear();
    ui->labelX_id_d1511_2->clear();
    ui->labelX_id_d1511_1->clear();
    ui->labelY_id_d1511_15->clear();
    ui->labelY_id_d1511_14->clear();
    ui->labelY_id_d1511_13->clear();
    ui->labelY_id_d1511_12->clear();
    ui->labelY_id_d1511_11->clear();
    ui->labelY_id_d1511_10->clear();
    ui->labelY_id_d1511_9->clear();
    ui->labelY_id_d1511_8->clear();
    ui->labelY_id_d1511_7->clear();
    ui->labelY_id_d1511_6->clear();
    ui->labelY_id_d1511_5->clear();
    ui->labelY_id_d1511_4->clear();
    ui->labelY_id_d1511_3->clear();
    ui->labelY_id_d1511_2->clear();
    ui->labelY_id_d1511_1->clear();
    ui->labelY_id_d1511_2_15->clear();
    ui->labelY_id_d1511_2_14->clear();
    ui->labelY_id_d1511_2_13->clear();
    ui->labelY_id_d1511_2_12->clear();
    ui->labelY_id_d1511_2_11->clear();
    ui->labelY_id_d1511_2_10->clear();
    ui->labelY_id_d1511_2_9->clear();
    ui->labelY_id_d1511_2_8->clear();
    ui->labelY_id_d1511_2_7->clear();
    ui->labelY_id_d1511_2_6->clear();
    ui->labelY_id_d1511_2_5->clear();
    ui->labelY_id_d1511_2_4->clear();
    ui->labelY_id_d1511_2_3->clear();
    ui->labelY_id_d1511_2_2->clear();
    ui->labelY_id_d1511_2_1->clear();
    ui->labelY_od_d1511_2_15->clear();
    ui->labelY_od_d1511_2_14->clear();
    ui->labelY_od_d1511_2_13->clear();
    ui->labelY_od_d1511_2_12->clear();
    ui->labelY_od_d1511_2_11->clear();
    ui->labelY_od_d1511_2_10->clear();
    ui->labelY_od_d1511_2_9->clear();
    ui->labelY_od_d1511_2_8->clear();
    ui->labelY_od_d1511_2_7->clear();
    ui->labelY_od_d1511_2_6->clear();
    ui->labelY_od_d1511_2_5->clear();
    ui->labelY_od_d1511_2_4->clear();
    ui->labelY_od_d1511_2_3->clear();
    ui->labelY_od_d1511_2_2->clear();
    ui->labelY_od_d1511_2_1->clear();
    resetLabelXd11();
}


/*!
 * \brief Очистка ячеек исходных данных во вкладке Шум для страницы для 11 бит.
 * \details Осуществляет переход  на вкладку интерфейса "Кодирование".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetLabelXd11() {
    ui->labelX_d_1511_2_11->clear();
    ui->labelX_d_1511_2_10->clear();
    ui->labelX_d_1511_2_9->clear();
    ui->labelX_d_1511_2_8->clear();
    ui->labelX_d_1511_2_7->clear();
    ui->labelX_d_1511_2_6->clear();
    ui->labelX_d_1511_2_5->clear();
    ui->labelX_d_1511_2_4->clear();
    ui->labelX_d_1511_2_3->clear();
    ui->labelX_d_1511_2_2->clear();
    ui->labelX_d_1511_2_1->clear();
}


/*!
 * \brief Очистка ячеек исходных данных во вкладке Шум для страницы для 4 бит.
 * \details Осуществляет переход  на вкладку интерфейса "Кодирование".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetLabelXd4() {
    ui->labelX_d_74_2_4->clear();
    ui->labelX_d_74_2_3->clear();
    ui->labelX_d_74_2_2->clear();
    ui->labelX_d_74_2_1->clear();
}

/*!
 * \brief Метод для сброса содержимого всех вкладов кодирования.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetEncoderData() {
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    resetPageEncoder74();
    resetPageEncoder84();
    resetPageEncoder1511();
    resetPageEncoder1611();
    resetPageEncoder1511d();
}


/*!
 * \brief Обработчик нажатия кнопки "Кодирование".
 * \details Осуществляет переход  на вкладку интерфейса "Кодирование".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonEncoding_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}


/*!
 * \brief Обработчик нажатия кнопки "Шум".
 * \details Осуществляет переход  на вкладку интерфейса "Шум".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonNoise_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}


/*!
 * \brief Обработчик нажатия кнопки "Декодирование".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonDecoding_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор формы ввода".
 * \details Выбирается ручное добавление или автоматическая генерация.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderFormInputNoise_clicked() {
    ui->horizontalSliderError1->setValue(0);
    ui->horizontalSliderError2->setValue(0);
    ui->horizontalSliderNoiseToAll->setValue(0);
    ui->horizontalSliderToCustom->setValue(0);
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderNoiseManual) {
        ui->horizontalSliderNoiseAuto->setValue(0);
        if (senderSlider->value() == 0) {
            noiseInputFlag = MANUAL;
        } else {
            noiseInputFlag = NO_MODE;
        }
        ui->horizontalSliderError1->setEnabled(false);
        ui->horizontalSliderError2->setEnabled(false);
        ui->horizontalSliderNoiseToAll->setEnabled(false);
        ui->horizontalSliderToCustom->setEnabled(false);
        ui->pushButtonAutoNoise->setEnabled(false);
    } else if (senderSlider == ui->horizontalSliderNoiseAuto) {
        ui->horizontalSliderNoiseManual->setValue(0);
        if (senderSlider->value() == 0) {
            noiseInputFlag = GENERATED;
            ui->horizontalSliderError1->setEnabled(true);
            ui->horizontalSliderError2->setEnabled(true);
            ui->horizontalSliderNoiseToAll->setEnabled(true);
            ui->horizontalSliderToCustom->setEnabled(true);
            ui->pushButtonAutoNoise->setEnabled(true);
        } else {
            noiseInputFlag = NO_MODE;
            ui->horizontalSliderError1->setEnabled(false);
            ui->horizontalSliderError2->setEnabled(false);
            ui->horizontalSliderNoiseToAll->setEnabled(false);
            ui->horizontalSliderToCustom->setEnabled(false);
            ui->pushButtonAutoNoise->setEnabled(false);
        }
    }
    bool enableButton = senderSlider == ui->horizontalSliderNoiseAuto ||
            (senderSlider == ui->horizontalSliderNoiseManual && senderSlider->value() != 0);
    if(enableButton) {
        removeEffect(ui->frame_15);
        setShadow(ui->frame_15);
        removeEffect(ui->frame_18);
        setShadow(ui->frame_18);
        removeEffect(ui->frame_19);
    } else {
        setBlur(ui->frame_15, BLUR_RADIUS_1);
        setBlur(ui->frame_18, BLUR_RADIUS_1);
        setBlur(ui->frame_19, BLUR_RADIUS_2);
    }
    ui->frame_15->update();
    ui->frame_18->update();
    ui->frame_19->update();
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор типа добавляемой ошибки".
 * \details Выбирается одиночная или двойная ошибка.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderErrorType_clicled() {
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderError1) {
        ui->horizontalSliderError2->setValue(0);
        if (senderSlider->value() == 0) {
            noiseErrorFlag = SINGLE;
        } else {
            noiseErrorFlag = NO_ERR;
        }
    } else if (senderSlider == ui->horizontalSliderError2) {
        ui->horizontalSliderError1->setValue(0);
        if (senderSlider->value() == 0) {
            noiseErrorFlag = DOUBLE;
        } else {
            noiseErrorFlag = NO_ERR;
        }
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Применить к".
 * \details Выбирается применение ко всем последовательностям или только в указанным.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderUseTo_clicked() {
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderNoiseToAll) {
        ui->horizontalSliderToCustom->setValue(0);
        if (senderSlider->value() == 0) {
            noiseImpactFlag = TO_ALL;
        } else {
            noiseImpactFlag = NO_IMPACT;
        }
    } else if (senderSlider == ui->horizontalSliderToCustom) {
        ui->horizontalSliderNoiseToAll->setValue(0);
        if (senderSlider->value() == 0) {
            noiseImpactFlag = TO_CUSTOM;
        } else {
            noiseImpactFlag = NO_IMPACT;
        }
    }
}


/*!
 * \brief Обработчик двойного клика по ClickableLabel.
 * \details Запускает процесс генерации ошибки по заданным параметрам.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::onDataLabel_doubleClicked() {
    if (noiseInputFlag == MANUAL && encodeAlgFlag != NO_ALG) {
        ClickableLabel *senderLabel = qobject_cast<ClickableLabel*>(sender());
        int indexSeq = ui->listWidget_2->currentRow();
        int indexVal = -1;
        switch (encodeAlgFlag) {
        case ALG_74: {
            if (senderLabel == ui->labelY_id_74_2_1) {
                indexVal = 0;
            } else if (senderLabel == ui->labelY_id_74_2_2) {
                indexVal = 1;
            } else if (senderLabel == ui->labelY_id_74_2_3) {
                indexVal = 2;
            } else if (senderLabel == ui->labelY_id_74_2_4) {
                indexVal = 3;
            } else if (senderLabel == ui->labelY_id_74_2_5) {
                indexVal = 4;
            } else if (senderLabel == ui->labelY_id_74_2_6) {
                indexVal = 5;
            } else if(senderLabel == ui->labelY_id_74_2_7) {
                indexVal = 6;
            }
            break;
        }
        case ALG_84: {
            if (senderLabel == ui->labelY_id_74_2_1) {
                indexVal = 0;
            } else if (senderLabel == ui->labelY_id_84_2_2) {
                indexVal = 1;
            } else if (senderLabel == ui->labelY_id_84_2_3) {
                indexVal = 2;
            } else if (senderLabel == ui->labelY_id_84_2_4) {
                indexVal = 3;
            } else if (senderLabel == ui->labelY_id_84_2_5) {
                indexVal = 4;
            } else if (senderLabel == ui->labelY_id_84_2_6) {
                indexVal = 5;
            } else if(senderLabel == ui->labelY_id_84_2_7) {
                indexVal = 6;
            } else if(senderLabel == ui->labelY_id_84_2_8) {
                indexVal = 7;
            }
            break;
        }
        case ALG_1511: {
            if (senderLabel == ui->labelY_id_1511_2_1) {
                indexVal = 0;
            } else if (senderLabel == ui->labelY_id_1511_2_2) {
                indexVal = 1;
            } else if (senderLabel == ui->labelY_id_1511_2_3) {
                indexVal = 2;
            } else if (senderLabel == ui->labelY_id_1511_2_4) {
                indexVal = 3;
            } else if (senderLabel == ui->labelY_id_1511_2_5) {
                indexVal = 4;
            } else if (senderLabel == ui->labelY_id_1511_2_6) {
                indexVal = 5;
            } else if(senderLabel == ui->labelY_id_1511_2_7) {
                indexVal = 6;
            } else if(senderLabel == ui->labelY_id_1511_2_8) {
                indexVal = 7;
            } else if(senderLabel == ui->labelY_id_1511_2_9) {
                indexVal = 8;
            } else if(senderLabel == ui->labelY_id_1511_2_10) {
                indexVal = 9;
            } else if(senderLabel == ui->labelY_id_1511_2_11) {
                indexVal = 10;
            } else if(senderLabel == ui->labelY_id_1511_2_12) {
                indexVal = 11;
            } else if(senderLabel == ui->labelY_id_1511_2_13) {
                indexVal = 12;
            } else if(senderLabel == ui->labelY_id_1511_2_14) {
                indexVal = 13;
            } else if(senderLabel == ui->labelY_id_1511_2_15) {
                indexVal = 14;
            }
            break;
        }
        case ALG_1611: {
            if (senderLabel == ui->labelY_id_1611_2_1) {
                indexVal = 0;
            } else if (senderLabel == ui->labelY_id_1611_2_2) {
                indexVal = 1;
            } else if (senderLabel == ui->labelY_id_1611_2_3) {
                indexVal = 2;
            } else if (senderLabel == ui->labelY_id_1611_2_4) {
                indexVal = 3;
            } else if (senderLabel == ui->labelY_id_1611_2_5) {
                indexVal = 4;
            } else if (senderLabel == ui->labelY_id_1611_2_6) {
                indexVal = 5;
            } else if(senderLabel == ui->labelY_id_1611_2_7) {
                indexVal = 6;
            } else if(senderLabel == ui->labelY_id_1611_2_8) {
                indexVal = 7;
            } else if(senderLabel == ui->labelY_id_1611_2_9) {
                indexVal = 8;
            } else if(senderLabel == ui->labelY_id_1611_2_10) {
                indexVal = 9;
            } else if(senderLabel == ui->labelY_id_1611_2_11) {
                indexVal = 10;
            } else if(senderLabel == ui->labelY_id_1611_2_12) {
                indexVal = 11;
            } else if(senderLabel == ui->labelY_id_1611_2_13) {
                indexVal = 12;
            } else if(senderLabel == ui->labelY_id_1611_2_14) {
                indexVal = 13;
            } else if(senderLabel == ui->labelY_id_1611_2_15) {
                indexVal = 14;
            } else if(senderLabel == ui->labelY_id_1611_2_16) {
                indexVal = 15;
            }
            break;
        }
        case ALG_1511d: {
            if (senderLabel == ui->labelY_id_d1511_2_1) {
                indexVal = 0;
            } else if (senderLabel == ui->labelY_id_d1511_2_2) {
                indexVal = 1;
            } else if (senderLabel == ui->labelY_id_d1511_2_3) {
                indexVal = 2;
            } else if (senderLabel == ui->labelY_id_d1511_2_4) {
                indexVal = 3;
            } else if (senderLabel == ui->labelY_id_d1511_2_5) {
                indexVal = 4;
            } else if (senderLabel == ui->labelY_id_d1511_2_6) {
                indexVal = 5;
            } else if(senderLabel == ui->labelY_id_d1511_2_7) {
                indexVal = 6;
            } else if(senderLabel == ui->labelY_id_d1511_2_8) {
                indexVal = 7;
            } else if(senderLabel == ui->labelY_id_d1511_2_9) {
                indexVal = 8;
            } else if(senderLabel == ui->labelY_id_d1511_2_10) {
                indexVal = 9;
            } else if(senderLabel == ui->labelY_id_d1511_2_11) {
                indexVal = 10;
            } else if(senderLabel == ui->labelY_id_d1511_2_12) {
                indexVal = 11;
            } else if(senderLabel == ui->labelY_id_d1511_2_13) {
                indexVal = 12;
            } else if(senderLabel == ui->labelY_id_d1511_2_14) {
                indexVal = 13;
            } else if(senderLabel == ui->labelY_id_d1511_2_15) {
                indexVal = 14;
            }
            break;
        }
        default: {
            break;
        }
        }
        if(indexSeq != -1 && indexVal != -1) {
            indexSeq = ui->listWidget_2->count() - indexSeq - 1;
            if (encodeAlgFlag != ALG_1511d) {
                modEncodedBitSeq.addError(indexSeq, indexVal);
                setBitsNoise(indexSeq, true);
            } else {
                modEncodedBigInt.addError(indexSeq, indexVal);
                setBitsNoise(indexSeq, true);
            }
        } else {
            NotificationForm *notification = new NotificationForm("Для добавления ошибки в ручном "
                                                                  "режиме выберите последовательность.");
            this->setEnabled(false);
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                notification->deleteLater();
                this->setEnabled(true);
            });
        }
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Генерация шума".
 * \details Запускает процесс генерации ошибки по заданным параметрам.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonAutoNoise_clicked() {
    if (noiseInputFlag == GENERATED && encodeAlgFlag != NO_ALG) {
        if(noiseErrorFlag != NO_ERR) {
            if(noiseImpactFlag != NO_IMPACT) {
                modEncodedBitSeq = clearEncodedBitSeq;
                modEncodedBigInt = clearEncodedBigInt;
                QList<int> listSeq;
                switch (noiseImpactFlag) {
                case TO_ALL: {
                    for(int i = 0; i < ui->listWidget_2->count(); ++i) {
                        listSeq.push_back(i);
                    }
                    break;
                }
                case TO_CUSTOM: {
                    QList<QListWidgetItem*> selectedItems = ui->listWidget_2->selectedItems();
                    for (const auto& item : selectedItems) {
                        listSeq.push_back(ui->listWidget_2->row(item));
                    }
                    break;
                }
                default: {
                    break; }
                }
                for(const int &i : listSeq) {
                    int index = ui->listWidget_2->count() - i - 1;
                    if(encodeAlgFlag != ALG_1511d) {
                        autoError(true, noiseErrorFlag, index);
                    } else {
                        autoError(false, noiseErrorFlag, index);
                    }
                    ui->listWidget_2->setCurrentRow(i);
                    setBitsNoise(index, false);
                    QEventLoop loop;
                    QTimer::singleShot(250, &loop, &QEventLoop::quit);
                    loop.exec();
                }
            } else {
                NotificationForm *notification = new NotificationForm("Для автоматического искажения последовательности "
                                                                      "выберите формат применения.");
                this->setEnabled(false);
                notification->show();
                QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                    notification->deleteLater();
                    this->setEnabled(true);
                });
            }
        } else {
            NotificationForm *notification = new NotificationForm("Для автоматического искажения последовательности "
                                                                  "выберите тип ошибки.");
            this->setEnabled(false);
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                notification->deleteLater();
                this->setEnabled(true);
            });
        }
    }
}


/*!
 * \brief Метод автоматически добавляет одиночную или двойную ошибку в указаннюу последовательность.
 * \param type Данные, с которыми работает метод: BitSequence или BigInteger.
 * \param typeError Тип ошибки: одиночная или двойная.
 * \param index Номер последовательности, которая подвергается воздействию.
 * \return Отсутствуют.
*/
void StudyForm::autoError(const bool &type, const int &typeError, const int &index) {
    int amount;
    if(type) {
        amount = clearEncodedBitSeq.getSize();
    } else {
        amount = clearEncodedBigInt.getSize();
    }
    if(typeError == 1) {
        if(type) {
            modEncodedBitSeq.addError(index, NumberGenerator::number(0, amount - 1));
        } else {
            modEncodedBigInt.addError(index, NumberGenerator::number(0, amount - 1));
        }
    } else if(typeError == 2) {
        int firstVal = NumberGenerator::number(0, amount - 1);
        int secondVal = NumberGenerator::number(0, amount - 1, firstVal);
        if(type) {
            modEncodedBitSeq.addError(index, firstVal);
            modEncodedBitSeq.addError(index, secondVal);
        } else {
            modEncodedBigInt.addError(index, firstVal);
            modEncodedBigInt.addError(index, secondVal);
        }
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Копировать".
 * \details Копирует данные о текущей закодированной последовательности.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonCopyData_clicked() {
    if(ui->listWidget->count() != 0) {
        decodeTypeFlag = encodeTypeFlag;
        switch (decodeTypeFlag) {
        case NO_TYPE: {
            ui->horizontalSliderDataType_3->setValue(0);
            ui->horizontalSliderDataType_4->setValue(0);
            break;
        }
        case NUMERIC: {
            ui->horizontalSliderDataType_3->setValue(1);
            ui->horizontalSliderDataType_4->setValue(0);
            break;
        }
        case TEXT: {
            ui->horizontalSliderDataType_3->setValue(0);
            ui->horizontalSliderDataType_4->setValue(1);
            break;
        }
        }
        if (decodeTypeFlag == TEXT) {
            setBlur(ui->frame_29, BLUR_RADIUS_1);
            decodeNumberFlag = NO_SYSTEM;
            ui->horizontalSliderNS2_2->setValue(0);
            ui->horizontalSliderNS4_2->setValue(0);
            ui->horizontalSliderNS8_2->setValue(0);
            ui->horizontalSliderNS10_2->setValue(0);
            ui->horizontalSliderNS16_2->setValue(0);
        } else {
            removeEffect(ui->frame_29);
            setShadow(ui->frame_29);
            decodeNumberFlag = encodeNumberFlag;
            switch (decodeNumberFlag) {
            case NO_SYSTEM: {
                ui->horizontalSliderNS2_2->setValue(0);
                ui->horizontalSliderNS4_2->setValue(0);
                ui->horizontalSliderNS8_2->setValue(0);
                ui->horizontalSliderNS10_2->setValue(0);
                ui->horizontalSliderNS16_2->setValue(0);
                break;
            }
            case BINARY: {
                ui->horizontalSliderNS2_2->setValue(1);
                ui->horizontalSliderNS4_2->setValue(0);
                ui->horizontalSliderNS8_2->setValue(0);
                ui->horizontalSliderNS10_2->setValue(0);
                ui->horizontalSliderNS16_2->setValue(0);
                break;
            }
            case QUATERNARY: {
                ui->horizontalSliderNS2_2->setValue(0);
                ui->horizontalSliderNS4_2->setValue(1);
                ui->horizontalSliderNS8_2->setValue(0);
                ui->horizontalSliderNS10_2->setValue(0);
                ui->horizontalSliderNS16_2->setValue(0);
                break;
            }
            case OCTAL: {
                ui->horizontalSliderNS2_2->setValue(0);
                ui->horizontalSliderNS4_2->setValue(0);
                ui->horizontalSliderNS8_2->setValue(1);
                ui->horizontalSliderNS10_2->setValue(0);
                ui->horizontalSliderNS16_2->setValue(0);
                break;
            }
            case DECIMAL: {
                ui->horizontalSliderNS2_2->setValue(0);
                ui->horizontalSliderNS4_2->setValue(0);
                ui->horizontalSliderNS8_2->setValue(0);
                ui->horizontalSliderNS10_2->setValue(1);
                ui->horizontalSliderNS16_2->setValue(0);
                break;
            }
            case HEXADECIMAL: {
                ui->horizontalSliderNS2_2->setValue(0);
                ui->horizontalSliderNS4_2->setValue(0);
                ui->horizontalSliderNS8_2->setValue(0);
                ui->horizontalSliderNS10_2->setValue(0);
                ui->horizontalSliderNS16_2->setValue(1);
                break;
            }
            }
        }
        if (decodeTypeFlag == NUMERIC) {
            ui->horizontalSliderNS2_2->setEnabled(true);
            ui->horizontalSliderNS4_2->setEnabled(true);
            ui->horizontalSliderNS8_2->setEnabled(true);
            ui->horizontalSliderNS10_2->setEnabled(true);
            ui->horizontalSliderNS16_2->setEnabled(true);
        } else {
            ui->horizontalSliderNS2_2->setEnabled(false);
            ui->horizontalSliderNS4_2->setEnabled(false);
            ui->horizontalSliderNS8_2->setEnabled(false);
            ui->horizontalSliderNS10_2->setEnabled(false);
            ui->horizontalSliderNS16_2->setEnabled(false);
        }
        ui->frame_29->update();
        if(decodeNumberFlag != DECIMAL) {
            ui->horizontalSliderEncoder1511d_2->setEnabled(false);
            setBlur(ui->frame_25, BLUR_RADIUS_1);
        } else {
            ui->frame_25->setEnabled(true);
            ui->horizontalSliderEncoder1511d_2->setEnabled(true);
            removeEffect(ui->frame_25);
        }
        ui->frame_25->update();
        decodeAlgFlag = encodeAlgFlag;
        switch (decodeAlgFlag) {
        case NO_ALG: {
            ui->horizontalSliderEncoder74_2->setValue(0);
            ui->horizontalSliderEncoder84_2->setValue(0);
            ui->horizontalSliderEncoder1511_2->setValue(0);
            ui->horizontalSliderEncoder1611_2->setValue(0);
            ui->horizontalSliderEncoder1511d_2->setValue(0);
            break;
        }
        case ALG_74: {
            ui->stackedWidget_6->setCurrentIndex(0);
            ui->horizontalSliderEncoder74_2->setValue(1);
            ui->horizontalSliderEncoder84_2->setValue(0);
            ui->horizontalSliderEncoder1511_2->setValue(0);
            ui->horizontalSliderEncoder1611_2->setValue(0);
            ui->horizontalSliderEncoder1511d_2->setValue(0);
            break;
        }
        case ALG_84: {
            ui->stackedWidget_6->setCurrentIndex(1);
            ui->horizontalSliderEncoder74_2->setValue(0);
            ui->horizontalSliderEncoder84_2->setValue(1);
            ui->horizontalSliderEncoder1511_2->setValue(0);
            ui->horizontalSliderEncoder1611_2->setValue(0);
            ui->horizontalSliderEncoder1511d_2->setValue(0);
            break;
        }
        case ALG_1511: {
            ui->stackedWidget_6->setCurrentIndex(2);
            ui->horizontalSliderEncoder74_2->setValue(0);
            ui->horizontalSliderEncoder84_2->setValue(0);
            ui->horizontalSliderEncoder1511_2->setValue(1);
            ui->horizontalSliderEncoder1611_2->setValue(0);
            ui->horizontalSliderEncoder1511d_2->setValue(0);
            break;
        }
        case ALG_1611: {
            ui->stackedWidget_6->setCurrentIndex(3);
            ui->horizontalSliderEncoder74_2->setValue(0);
            ui->horizontalSliderEncoder84_2->setValue(0);
            ui->horizontalSliderEncoder1511_2->setValue(0);
            ui->horizontalSliderEncoder1611_2->setValue(1);
            ui->horizontalSliderEncoder1511d_2->setValue(0);
            break;
        }
        case ALG_1511d: {
            ui->stackedWidget_6->setCurrentIndex(4);
            ui->horizontalSliderEncoder74_2->setValue(0);
            ui->horizontalSliderEncoder84_2->setValue(0);
            ui->horizontalSliderEncoder1511_2->setValue(0);
            ui->horizontalSliderEncoder1611_2->setValue(0);
            ui->horizontalSliderEncoder1511d_2->setValue(1);
            break;
        }
        }
        if(decodeAlgFlag == ALG_1511d) {
            ui->textEditData_2->setText(modEncodedBigInt.getSecond());
        } else {
            ui->textEditData_2->setText(modEncodedBitSeq.getSecond());
        }
    } else {
        NotificationForm *notification = new NotificationForm("При копировании данных произошла ошибка. "
                                                              "Сначала необходимо провести кодирование.");
        this->setEnabled(false);
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, this, [=]() {
            notification->deleteLater();
            this->setEnabled(true);
        });
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Декодирование".
 * \details Осуществл.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonDecode_clicked() {
    if(decodeTypeFlag == NO_TYPE || decodeNumberFlag == NO_SYSTEM) {
        NotificationForm *notification = new NotificationForm("Декодирование невозможно. Выберите тип данных.");
        this->setEnabled(false);
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, this, [=]() {
            notification->deleteLater();
            this->setEnabled(true);
        });
    } else {
        QString data = ui->textEditData_2->toPlainText();
        if (data.length()) {
            if(BINARY_REGEX.match(data).hasMatch() ||
                    (decodeAlgFlag == ALG_1511d && DECIMAL_REGEX.match(data).hasMatch())) {
                BitSequence seq = BitSequence();
                switch (decodeAlgFlag) {
                case NO_ALG: {
                    NotificationForm *notification = new NotificationForm("Декодирование невозможно. "
                                                                          "Выберите алгоритм.");
                    this->setEnabled(false);
                    notification->show();
                    QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                        notification->deleteLater();
                        this->setEnabled(true);
                    });
                    return;
                }
                case ALG_74: {
                    Converter::toBinary(seq, data, 2);
                    setListSeq(7, seq, ui->listWidget_3);
                    decodedBitData = Decoder74::start(BitSequenceShell(seq, ALG_74, 7, true));
                    break;
                }
                case ALG_84: {
                    Converter::toBinary(seq, data, 2);
                    setListSeq(8, seq, ui->listWidget_3);
                    decodedBitData = Decoder84::start(BitSequenceShell(seq, ALG_84, 8, true));
                    break;
                }
                case ALG_1511: {
                    Converter::toBinary(seq, data, 2);
                    setListSeq(15, seq, ui->listWidget_3);
                    decodedBitData = Decoder1511::start(BitSequenceShell(seq, ALG_1511, 15, true));
                    break;
                }
                case ALG_1611: {
                    Converter::toBinary(seq, data, 2);
                    setListSeq(16, seq, ui->listWidget_3);
                    decodedBitData = Decoder1611::start(BitSequenceShell(seq, ALG_1611, 16, true));
                    break;
                }
                case ALG_1511d: {
                    BigInteger tmp(data);
                    setListInt(15, tmp, ui->listWidget_3);
                    decodedIntData = DecoderDecimal1511::start(BigIntegerShell(tmp, ALG_1511d, 15, true));
                    break;
                }
                }
                if (decodeTypeFlag == TEXT) {
                    QString output = decodedBitData.first.getFirst().remove(LEADING_REGEX);
                    output = Converter::toText(output);
                    ui->textEditData_3->setText(output);
                } else if (decodeTypeFlag == NUMERIC) {
                    if (decodeAlgFlag == ALG_1511d && decodeNumberFlag == DECIMAL) {
                        ui->textEditData_3->setText(decodedIntData.first.getFirst().remove(LEADING_REGEX));
                    } else {
                        QString output = decodedBitData.first.getFirst().remove(LEADING_REGEX);
                        switch (decodeNumberFlag) {
                        case BINARY: {
                            break;
                        }
                        case QUATERNARY: {
                            output = Converter::toQuaternary(output, 2);
                            break;
                        }
                        case OCTAL: {
                            output = Converter::toOctal(output, 2);
                            break;
                        }
                        case DECIMAL: {
                            BigInteger decimal = Converter::toDecimal(output, 2);
                            output = decimal.toString();
                            break;
                        }
                        case HEXADECIMAL: {
                            output = Converter::toHexadecimal(output, 2);
                            break;
                        }
                        default: {
                            break;
                        }
                        }
                         ui->textEditData_3->setText(output);
                    }
                }
            } else {
                NotificationForm *notification = new NotificationForm("Декодирование невозможно. Введены неверные входные данные.");
                this->setEnabled(false);
                notification->show();
                QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                    notification->deleteLater();
                    this->setEnabled(true);
                });
            }
        } else {
            NotificationForm *notification = new NotificationForm("Декодирование невозможно. Отсутствуют входные данные.");
            this->setEnabled(false);
            notification->show();
            QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                notification->deleteLater();
                this->setEnabled(true);
            });
        }
    }
}


/*!
 * \brief Метод для установки содержимого ячеек значений для вкладки "Декодирование".
 * \param index Индекс последовательности.
 * \return Отсутствуют.
*/
void StudyForm::setBitsDecoding(const int &index) {
    QString eData, dData, syndrom;
    int syndromIndex = -1;
    if(decodeAlgFlag != ALG_1511d) {
        eData = decodedBitData.first[index].second.toString();
        dData = decodedBitData.first[index].first.toString();
        syndrom = decodedBitData.second.at(index).toString();
        switch (decodeAlgFlag) {
        case NO_ALG: {
            break;
        }
        case ALG_74: {
            syndromIndex = decodedBitData.second.at(index).toDecimal();
            ui->labelY_id_d_74_7->setText(eData.at(0));
            ui->labelY_id_d_74_6->setText(eData.at(1));
            ui->labelY_id_d_74_5->setText(eData.at(2));
            ui->labelY_id_d_74_4->setText(eData.at(3));
            ui->labelY_id_d_74_3->setText(eData.at(4));
            ui->labelY_id_d_74_2->setText(eData.at(5));
            ui->labelY_id_d_74_1->setText(eData.at(6));
            ui->labelY_id_d_74_2_7->setText(eData.at(0));
            ui->labelY_id_d_74_2_6->setText(eData.at(1));
            ui->labelY_id_d_74_2_5->setText(eData.at(2));
            ui->labelY_id_d_74_2_4->setText(syndrom.at(0));
            ui->labelY_id_d_74_2_3->setText(eData.at(4));
            ui->labelY_id_d_74_2_2->setText(syndrom.at(1));
            ui->labelY_id_d_74_2_1->setText(syndrom.at(2));
            ui->labelX_74_errorIn->setText(QString::number(syndromIndex));
            if(syndromIndex) {
                ui->labelX_74_errorType->setText(QString("Одиночная"));
            } else {
                ui->labelX_74_errorType->setText(QString("Отсутствует"));
            }
            ui->labelX_od_d_74_4->setText(dData.at(0));
            ui->labelX_od_d_74_3->setText(dData.at(1));
            ui->labelX_od_d_74_2->setText(dData.at(2));
            ui->labelX_od_d_74_1->setText(dData.at(3));
            break;
        }
        case ALG_84: {
            syndromIndex = decodedBitData.second.at(index).subsequence(1, 3).toDecimal();
            ui->labelY_id_d_84_8->setText(eData.at(0));
            ui->labelY_id_d_84_7->setText(eData.at(1));
            ui->labelY_id_d_84_6->setText(eData.at(2));
            ui->labelY_id_d_84_5->setText(eData.at(3));
            ui->labelY_id_d_84_4->setText(eData.at(4));
            ui->labelY_id_d_84_3->setText(eData.at(5));
            ui->labelY_id_d_84_2->setText(eData.at(6));
            ui->labelY_id_d_84_1->setText(eData.at(7));
            ui->labelY_id_d_84_2_8->setText(eData.at(0));
            ui->labelY_id_d_84_2_7->setText(eData.at(1));
            ui->labelY_id_d_84_2_6->setText(eData.at(2));
            ui->labelY_id_d_84_2_5->setText(syndrom.at(0));
            ui->labelY_id_d_84_2_4->setText(eData.at(4));
            ui->labelY_id_d_84_2_3->setText(syndrom.at(1));
            ui->labelY_id_d_84_2_2->setText(syndrom.at(2));
            ui->labelY_id_d_84_2_1->setText(syndrom.at(3));
            ui->labelX_84_errorIn->setText(QString::number(syndromIndex));
            if(!decodedBitData.second[index].toDecimal()) {
                ui->labelX_84_errorType->setText(QString("Отсутствует"));
            } else {
                if(decodedBitData.second[index][0]) {
                    ui->labelX_84_errorType->setText(QString("Одиночная"));
                } else {
                    ui->labelX_84_errorType->setText(QString("Двойная"));
                }
            }
            ui->labelX_od_d_84_4->setText(dData.at(0));
            ui->labelX_od_d_84_3->setText(dData.at(1));
            ui->labelX_od_d_84_2->setText(dData.at(2));
            ui->labelX_od_d_84_1->setText(dData.at(3));
            break;
        }
        case ALG_1511: {
            syndromIndex = decodedBitData.second.at(index).toDecimal();
            ui->labelY_id_d_1511_15->setText(eData.at(0));
            ui->labelY_id_d_1511_14->setText(eData.at(1));
            ui->labelY_id_d_1511_13->setText(eData.at(2));
            ui->labelY_id_d_1511_12->setText(eData.at(3));
            ui->labelY_id_d_1511_11->setText(eData.at(4));
            ui->labelY_id_d_1511_10->setText(eData.at(5));
            ui->labelY_id_d_1511_9->setText(eData.at(6));
            ui->labelY_id_d_1511_8->setText(eData.at(7));
            ui->labelY_id_d_1511_7->setText(eData.at(8));
            ui->labelY_id_d_1511_6->setText(eData.at(9));
            ui->labelY_id_d_1511_5->setText(eData.at(10));
            ui->labelY_id_d_1511_4->setText(eData.at(11));
            ui->labelY_id_d_1511_3->setText(eData.at(12));
            ui->labelY_id_d_1511_2->setText(eData.at(13));
            ui->labelY_id_d_1511_1->setText(eData.at(14));
            ui->labelY_id_d_1511_2_15->setText(eData.at(0));
            ui->labelY_id_d_1511_2_14->setText(eData.at(1));
            ui->labelY_id_d_1511_2_13->setText(eData.at(2));
            ui->labelY_id_d_1511_2_12->setText(eData.at(3));
            ui->labelY_id_d_1511_2_11->setText(eData.at(4));
            ui->labelY_id_d_1511_2_10->setText(eData.at(5));
            ui->labelY_id_d_1511_2_9->setText(eData.at(6));
            ui->labelY_id_d_1511_2_8->setText(syndrom.at(0));
            ui->labelY_id_d_1511_2_7->setText(eData.at(8));
            ui->labelY_id_d_1511_2_6->setText(eData.at(9));
            ui->labelY_id_d_1511_2_5->setText(eData.at(10));
            ui->labelY_id_d_1511_2_4->setText(syndrom.at(1));
            ui->labelY_id_d_1511_2_3->setText(eData.at(12));
            ui->labelY_id_d_1511_2_2->setText(syndrom.at(2));
            ui->labelY_id_d_1511_2_1->setText(syndrom.at(3));
            ui->labelX_1511_errorIn->setText(QString::number(syndromIndex));
            if(syndromIndex) {
                ui->labelX_1511_errorType->setText(QString("Одиночная"));
            } else {
                ui->labelX_1511_errorType->setText(QString("Отсутствует"));
            }
            ui->labelX_od_d_1511_11->setText(dData.at(0));
            ui->labelX_od_d_1511_10->setText(dData.at(1));
            ui->labelX_od_d_1511_9->setText(dData.at(2));
            ui->labelX_od_d_1511_8->setText(dData.at(3));
            ui->labelX_od_d_1511_7->setText(dData.at(4));
            ui->labelX_od_d_1511_6->setText(dData.at(5));
            ui->labelX_od_d_1511_5->setText(dData.at(6));
            ui->labelX_od_d_1511_4->setText(dData.at(7));
            ui->labelX_od_d_1511_3->setText(dData.at(8));
            ui->labelX_od_d_1511_2->setText(dData.at(9));
            ui->labelX_od_d_1511_1->setText(dData.at(10));
            break;
        }
        case ALG_1611: {
            syndromIndex = decodedBitData.second.at(index).subsequence(1, 4).toDecimal();
            ui->labelY_id_d_1611_15->setText(eData.at(0));
            ui->labelY_id_d_1611_14->setText(eData.at(1));
            ui->labelY_id_d_1611_13->setText(eData.at(2));
            ui->labelY_id_d_1611_12->setText(eData.at(3));
            ui->labelY_id_d_1611_11->setText(eData.at(4));
            ui->labelY_id_d_1611_10->setText(eData.at(5));
            ui->labelY_id_d_1611_9->setText(eData.at(6));
            ui->labelY_id_d_1611_8->setText(eData.at(7));
            ui->labelY_id_d_1611_7->setText(eData.at(8));
            ui->labelY_id_d_1611_6->setText(eData.at(9));
            ui->labelY_id_d_1611_5->setText(eData.at(10));
            ui->labelY_id_d_1611_4->setText(eData.at(11));
            ui->labelY_id_d_1611_3->setText(eData.at(12));
            ui->labelY_id_d_1611_2->setText(eData.at(13));
            ui->labelY_id_d_1611_1->setText(eData.at(14));
            ui->labelY_id_d_1611_2_15->setText(eData.at(0));
            ui->labelY_id_d_1611_2_14->setText(eData.at(1));
            ui->labelY_id_d_1611_2_13->setText(eData.at(2));
            ui->labelY_id_d_1611_2_12->setText(eData.at(3));
            ui->labelY_id_d_1611_2_11->setText(eData.at(4));
            ui->labelY_id_d_1611_2_10->setText(eData.at(5));
            ui->labelY_id_d_1611_2_9->setText(syndrom.at(0));
            ui->labelY_id_d_1611_2_8->setText(eData.at(7));
            ui->labelY_id_d_1611_2_7->setText(eData.at(8));
            ui->labelY_id_d_1611_2_6->setText(eData.at(9));
            ui->labelY_id_d_1611_2_5->setText(syndrom.at(1));
            ui->labelY_id_d_1611_2_4->setText(eData.at(11));
            ui->labelY_id_d_1611_2_3->setText(syndrom.at(2));
            ui->labelY_id_d_1611_2_2->setText(syndrom.at(3));
            ui->labelY_id_d_1611_2_1->setText(syndrom.at(4));
            ui->labelX_1611_errorIn->setText(QString::number(syndromIndex));
            if(!decodedBitData.second[index].toDecimal()) {
                ui->labelX_1611_errorType->setText(QString("Отсутствует"));
            } else {
                if(decodedBitData.second[index][0]) {
                    ui->labelX_1611_errorType->setText(QString("Одиночная"));
                } else {
                    ui->labelX_1611_errorType->setText(QString("Двойная"));
                }
            }
            ui->labelX_od_d_1611_11->setText(dData.at(0));
            ui->labelX_od_d_1611_10->setText(dData.at(1));
            ui->labelX_od_d_1611_9->setText(dData.at(2));
            ui->labelX_od_d_1611_8->setText(dData.at(3));
            ui->labelX_od_d_1611_7->setText(dData.at(4));
            ui->labelX_od_d_1611_6->setText(dData.at(5));
            ui->labelX_od_d_1611_5->setText(dData.at(6));
            ui->labelX_od_d_1611_4->setText(dData.at(7));
            ui->labelX_od_d_1611_3->setText(dData.at(8));
            ui->labelX_od_d_1611_2->setText(dData.at(9));
            ui->labelX_od_d_1611_1->setText(dData.at(10));
            break;
        }
        default: {
            break;
        }
        }
    } else {
        eData = decodedIntData.first[index].second.toString();
        dData = decodedIntData.first[index].first.toString();
        syndrom = decodedIntData.second.at(index).toString();
        BitSequence seq = BitSequence();
        seq.append(decodedIntData.second.at(index)[0] > 0);
        seq.append(decodedIntData.second.at(index)[1] > 0);
        seq.append(decodedIntData.second.at(index)[2] > 0);
        seq.append(decodedIntData.second.at(index)[3] > 0);
        syndromIndex = seq.toDecimal();
        ui->labelY_id_d_d1511_15->setText(eData.at(0));
        ui->labelY_id_d_d1511_14->setText(eData.at(1));
        ui->labelY_id_d_d1511_13->setText(eData.at(2));
        ui->labelY_id_d_d1511_12->setText(eData.at(3));
        ui->labelY_id_d_d1511_11->setText(eData.at(4));
        ui->labelY_id_d_d1511_10->setText(eData.at(5));
        ui->labelY_id_d_d1511_9->setText(eData.at(6));
        ui->labelY_id_d_d1511_8->setText(eData.at(7));
        ui->labelY_id_d_d1511_7->setText(eData.at(8));
        ui->labelY_id_d_d1511_6->setText(eData.at(9));
        ui->labelY_id_d_d1511_5->setText(eData.at(10));
        ui->labelY_id_d_d1511_4->setText(eData.at(11));
        ui->labelY_id_d_d1511_3->setText(eData.at(12));
        ui->labelY_id_d_d1511_2->setText(eData.at(13));
        ui->labelY_id_d_d1511_1->setText(eData.at(14));
        ui->labelY_id_d_d1511_2_15->setText(eData.at(0));
        ui->labelY_id_d_d1511_2_14->setText(eData.at(1));
        ui->labelY_id_d_d1511_2_13->setText(eData.at(2));
        ui->labelY_id_d_d1511_2_12->setText(eData.at(3));
        ui->labelY_id_d_d1511_2_11->setText(eData.at(4));
        ui->labelY_id_d_d1511_2_10->setText(eData.at(5));
        ui->labelY_id_d_d1511_2_9->setText(eData.at(6));
        ui->labelY_id_d_d1511_2_8->setText(syndrom.at(0));
        ui->labelY_id_d_d1511_2_7->setText(eData.at(8));
        ui->labelY_id_d_d1511_2_6->setText(eData.at(9));
        ui->labelY_id_d_d1511_2_5->setText(eData.at(10));
        ui->labelY_id_d_d1511_2_4->setText(syndrom.at(1));
        ui->labelY_id_d_d1511_2_3->setText(eData.at(12));
        ui->labelY_id_d_d1511_2_2->setText(syndrom.at(2));
        ui->labelY_id_d_d1511_2_1->setText(syndrom.at(3));
        ui->labelX_d1511_errorIn->setText(QString::number(syndromIndex));
        if(syndromIndex) {
            ui->labelX_d1511_errorType->setText(QString("Одиночная"));
        } else {
            ui->labelX_d1511_errorType->setText(QString("Отсутствует"));
        }
        ui->labelX_od_d_d1511_11->setText(dData.at(0));
        ui->labelX_od_d_d1511_10->setText(dData.at(1));
        ui->labelX_od_d_d1511_9->setText(dData.at(2));
        ui->labelX_od_d_d1511_8->setText(dData.at(3));
        ui->labelX_od_d_d1511_7->setText(dData.at(4));
        ui->labelX_od_d_d1511_6->setText(dData.at(5));
        ui->labelX_od_d_d1511_5->setText(dData.at(6));
        ui->labelX_od_d_d1511_4->setText(dData.at(7));
        ui->labelX_od_d_d1511_3->setText(dData.at(8));
        ui->labelX_od_d_d1511_2->setText(dData.at(9));
        ui->labelX_od_d_d1511_1->setText(dData.at(10));
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор типа входных данных" во вкладке Декодирование.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderDataType_2_clicked() {
    resetEncoderNS_2();
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderDataType_3) {
        ui->horizontalSliderDataType_4->setValue(0);
        if(senderSlider->value() == 0) {
            decodeTypeFlag = NUMERIC;
            setEnabledNS_2(true);
        } else {
            decodeTypeFlag = NO_TYPE;
            setEnabledNS_2(false);
        }
    } else if (senderSlider == ui->horizontalSliderDataType_4) {
        ui->horizontalSliderDataType_3->setValue(0);
        if(senderSlider->value() == 0) {
            decodeTypeFlag = TEXT;
            setEnabledNS_2(false);
        } else {
            decodeTypeFlag = NO_TYPE;
            setEnabledNS_2(false);
        }
    }
    bool enableFrame = senderSlider != ui->horizontalSliderDataType_4 ||
                       (senderSlider->value() == 1);
    if (enableFrame) {
        removeEffect(ui->frame_29);
        setShadow(ui->frame_29);
        removeEffect(ui->frame_25);
    } else {
        setBlur(ui->frame_29, BLUR_RADIUS_1);
        setBlur(ui->frame_25, BLUR_RADIUS_2);
    }
    ui->horizontalSliderEncoder1511d_2->setEnabled(enableFrame);
    ui->frame_29->update();
    ui->frame_25->update();
}


/*!
* \brief Метод для включения/выключения выбора алгоритмов при декодировани.
* \param Flag Включение/выключение.
* \return Отсутствуют.
*/
void StudyForm::setEnabledNS_2(const bool &flag) {
    ui->horizontalSliderNS2_2->setEnabled(flag);
    ui->horizontalSliderNS4_2->setEnabled(flag);
    ui->horizontalSliderNS8_2->setEnabled(flag);
    ui->horizontalSliderNS10_2->setEnabled(flag);
    ui->horizontalSliderNS16_2->setEnabled(flag);
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор системы счисления" при декодировании.
 * \details Обрабатывает нажатие кнопки выбора системы счисления.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderNS_2_clicked() {
    resetAlgo_2();
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    QList<QSlider*> sliders = { ui->horizontalSliderNS2_2,
                                ui->horizontalSliderNS4_2,
                                ui->horizontalSliderNS8_2,
                                ui->horizontalSliderNS10_2,
                                ui->horizontalSliderNS16_2, };
    for (QSlider *slider : sliders) {
        if (slider != senderSlider) {
            slider->setValue(0);
        }
    }
    if (senderSlider->value() == 0) {
        if (senderSlider == ui->horizontalSliderNS2_2)
            decodeNumberFlag = BINARY;
        else if (senderSlider == ui->horizontalSliderNS4_2)
            decodeNumberFlag = QUATERNARY;
        else if (senderSlider == ui->horizontalSliderNS8_2)
            decodeNumberFlag = OCTAL;
        else if (senderSlider == ui->horizontalSliderNS10_2)
            decodeNumberFlag = DECIMAL;
        else if (senderSlider == ui->horizontalSliderNS16_2)
            decodeNumberFlag = HEXADECIMAL;
    } else {
        decodeNumberFlag = NO_SYSTEM;
    }
    bool enableFrame = senderSlider == ui->horizontalSliderNS10_2 || senderSlider->value() == 1;
    ui->horizontalSliderEncoder1511d_2->setEnabled(enableFrame);
    if(enableFrame) {
        removeEffect(ui->frame_25);
    } else {
        setBlur(ui->frame_25, BLUR_RADIUS_1);
    }
    ui->frame_25->update();
}


/*!
 * \brief Метод для сброса системы счисления числовых данных при декодировании.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetEncoderNS_2() {
    ui->horizontalSliderNS2_2->setValue(0);
    ui->horizontalSliderNS4_2->setValue(0);
    ui->horizontalSliderNS8_2->setValue(0);
    ui->horizontalSliderNS10_2->setValue(0);
    ui->horizontalSliderNS16_2->setValue(0);
}


/*!
 * \brief Метод для сброса выбранного алгоритма декодирования.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetAlgo_2() {
    ui->horizontalSliderEncoder74_2->setValue(0);
    ui->horizontalSliderEncoder84_2->setValue(0);
    ui->horizontalSliderEncoder1511_2->setValue(0);
    ui->horizontalSliderEncoder1611_2->setValue(0);
    ui->horizontalSliderEncoder1511d_2->setValue(0);
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор алгоритма декодирования".
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderDecoder_clicked() {
    resetDecoderData();
    QSlider *senderSlider = qobject_cast<QSlider*>(sender());
    QList<QSlider*> sliders = { ui->horizontalSliderEncoder74_2,
                                ui->horizontalSliderEncoder84_2,
                                ui->horizontalSliderEncoder1511_2,
                                ui->horizontalSliderEncoder1611_2,
                                ui->horizontalSliderEncoder1511d_2, };
    for (QSlider *slider : sliders) {
        if(slider != senderSlider) {
            slider->setValue(0);
        }
    }
    if (!senderSlider->value()) {
        if(senderSlider == ui->horizontalSliderEncoder74_2) {
            decodeAlgFlag = ALG_74;
        } else if(senderSlider == ui->horizontalSliderEncoder84_2) {
            decodeAlgFlag = ALG_84;
        } else if(senderSlider == ui->horizontalSliderEncoder1511_2) {
            decodeAlgFlag = ALG_1511;
        } else if(senderSlider == ui->horizontalSliderEncoder1611_2) {
            decodeAlgFlag = ALG_1611;
        } else if(senderSlider == ui->horizontalSliderEncoder1511d_2) {
            decodeAlgFlag = ALG_1511d;
        }
        ui->stackedWidget_6->setCurrentIndex(decodeAlgFlag);
    } else {
        decodeAlgFlag = NO_ALG;
    }
}


/*!
 * \brief Метод для сброса содержимого всех вкладок декодирования.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetDecoderData() {
    ui->textEditData_3->clear();
    ui->listWidget_3->clear();
    resetPageDecoder74();
    resetPageDecoder84();
    resetPageDecoder1511();
    resetPageDecoder1611();
    resetPageDecoder1511d();
}


/*!
 * \brief Метод для сброса содержимого вкладки декодирования 7-4.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageDecoder74() {
    ui->labelY_id_d_74_7->clear();
    ui->labelY_id_d_74_6->clear();
    ui->labelY_id_d_74_5->clear();
    ui->labelY_id_d_74_4->clear();
    ui->labelY_id_d_74_3->clear();
    ui->labelY_id_d_74_2->clear();
    ui->labelY_id_d_74_1->clear();
    ui->labelY_id_d_74_2_7->clear();
    ui->labelY_id_d_74_2_6->clear();
    ui->labelY_id_d_74_2_5->clear();
    ui->labelY_id_d_74_2_4->clear();
    ui->labelY_id_d_74_2_3->clear();
    ui->labelY_id_d_74_2_2->clear();
    ui->labelY_id_d_74_2_1->clear();
    ui->labelX_74_errorIn->clear();
    ui->labelX_74_errorType->clear();
    ui->labelX_od_d_74_4->clear();
    ui->labelX_od_d_74_3->clear();
    ui->labelX_od_d_74_2->clear();
    ui->labelX_od_d_74_1->clear();
}


/*!
 * \brief Метод для сброса содержимого вкладки декодирования 8-4.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageDecoder84() {
    ui->labelY_id_d_84_8->clear();
    ui->labelY_id_d_84_7->clear();
    ui->labelY_id_d_84_6->clear();
    ui->labelY_id_d_84_5->clear();
    ui->labelY_id_d_84_4->clear();
    ui->labelY_id_d_84_3->clear();
    ui->labelY_id_d_84_2->clear();
    ui->labelY_id_d_84_1->clear();
    ui->labelY_id_d_84_2_8->clear();
    ui->labelY_id_d_84_2_7->clear();
    ui->labelY_id_d_84_2_6->clear();
    ui->labelY_id_d_84_2_5->clear();
    ui->labelY_id_d_84_2_4->clear();
    ui->labelY_id_d_84_2_3->clear();
    ui->labelY_id_d_84_2_2->clear();
    ui->labelY_id_d_84_2_1->clear();
    ui->labelX_84_errorIn->clear();
    ui->labelX_84_errorType->clear();
    ui->labelX_od_d_84_4->clear();
    ui->labelX_od_d_84_3->clear();
    ui->labelX_od_d_84_2->clear();
    ui->labelX_od_d_84_1->clear();
}


/*!
 * \brief Метод для сброса содержимого вкладки декодирования 15-11.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageDecoder1511() {
    ui->labelY_id_d_1511_15->clear();
    ui->labelY_id_d_1511_14->clear();
    ui->labelY_id_d_1511_13->clear();
    ui->labelY_id_d_1511_12->clear();
    ui->labelY_id_d_1511_11->clear();
    ui->labelY_id_d_1511_10->clear();
    ui->labelY_id_d_1511_9->clear();
    ui->labelY_id_d_1511_8->clear();
    ui->labelY_id_d_1511_7->clear();
    ui->labelY_id_d_1511_6->clear();
    ui->labelY_id_d_1511_5->clear();
    ui->labelY_id_d_1511_4->clear();
    ui->labelY_id_d_1511_3->clear();
    ui->labelY_id_d_1511_2->clear();
    ui->labelY_id_d_1511_1->clear();
    ui->labelY_id_d_1511_2_15->clear();
    ui->labelY_id_d_1511_2_14->clear();
    ui->labelY_id_d_1511_2_13->clear();
    ui->labelY_id_d_1511_2_12->clear();
    ui->labelY_id_d_1511_2_11->clear();
    ui->labelY_id_d_1511_2_10->clear();
    ui->labelY_id_d_1511_2_9->clear();
    ui->labelY_id_d_1511_2_8->clear();
    ui->labelY_id_d_1511_2_7->clear();
    ui->labelY_id_d_1511_2_6->clear();
    ui->labelY_id_d_1511_2_5->clear();
    ui->labelY_id_d_1511_2_4->clear();
    ui->labelY_id_d_1511_2_3->clear();
    ui->labelY_id_d_1511_2_2->clear();
    ui->labelY_id_d_1511_2_1->clear();
    ui->labelX_1511_errorIn->clear();
    ui->labelX_1511_errorType->clear();
    ui->labelX_od_d_1511_11->clear();
    ui->labelX_od_d_1511_10->clear();
    ui->labelX_od_d_1511_9->clear();
    ui->labelX_od_d_1511_8->clear();
    ui->labelX_od_d_1511_7->clear();
    ui->labelX_od_d_1511_6->clear();
    ui->labelX_od_d_1511_5->clear();
    ui->labelX_od_d_1511_4->clear();
    ui->labelX_od_d_1511_3->clear();
    ui->labelX_od_d_1511_2->clear();
    ui->labelX_od_d_1511_1->clear();
}


/*!
 * \brief Метод для сброса содержимого вкладки декодирования 16-11.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageDecoder1611() {
    ui->labelY_id_d_1611_15->clear();
    ui->labelY_id_d_1611_14->clear();
    ui->labelY_id_d_1611_13->clear();
    ui->labelY_id_d_1611_12->clear();
    ui->labelY_id_d_1611_11->clear();
    ui->labelY_id_d_1611_10->clear();
    ui->labelY_id_d_1611_9->clear();
    ui->labelY_id_d_1611_8->clear();
    ui->labelY_id_d_1611_7->clear();
    ui->labelY_id_d_1611_6->clear();
    ui->labelY_id_d_1611_5->clear();
    ui->labelY_id_d_1611_4->clear();
    ui->labelY_id_d_1611_3->clear();
    ui->labelY_id_d_1611_2->clear();
    ui->labelY_id_d_1611_1->clear();
    ui->labelY_id_d_1611_2_15->clear();
    ui->labelY_id_d_1611_2_14->clear();
    ui->labelY_id_d_1611_2_13->clear();
    ui->labelY_id_d_1611_2_12->clear();
    ui->labelY_id_d_1611_2_11->clear();
    ui->labelY_id_d_1611_2_10->clear();
    ui->labelY_id_d_1611_2_9->clear();
    ui->labelY_id_d_1611_2_8->clear();
    ui->labelY_id_d_1611_2_7->clear();
    ui->labelY_id_d_1611_2_6->clear();
    ui->labelY_id_d_1611_2_5->clear();
    ui->labelY_id_d_1611_2_4->clear();
    ui->labelY_id_d_1611_2_3->clear();
    ui->labelY_id_d_1611_2_2->clear();
    ui->labelY_id_d_1611_2_1->clear();
    ui->labelX_1611_errorIn->clear();
    ui->labelX_1611_errorType->clear();
    ui->labelX_od_d_1611_11->clear();
    ui->labelX_od_d_1611_10->clear();
    ui->labelX_od_d_1611_9->clear();
    ui->labelX_od_d_1611_8->clear();
    ui->labelX_od_d_1611_7->clear();
    ui->labelX_od_d_1611_6->clear();
    ui->labelX_od_d_1611_5->clear();
    ui->labelX_od_d_1611_4->clear();
    ui->labelX_od_d_1611_3->clear();
    ui->labelX_od_d_1611_2->clear();
    ui->labelX_od_d_1611_1->clear();
}


/*!
 * \brief Метод для сброса содержимого вкладки десятичного декодирования 15-11.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPageDecoder1511d() {
    ui->labelY_id_d_d1511_15->clear();
    ui->labelY_id_d_d1511_14->clear();
    ui->labelY_id_d_d1511_13->clear();
    ui->labelY_id_d_d1511_12->clear();
    ui->labelY_id_d_d1511_11->clear();
    ui->labelY_id_d_d1511_10->clear();
    ui->labelY_id_d_d1511_9->clear();
    ui->labelY_id_d_d1511_8->clear();
    ui->labelY_id_d_d1511_7->clear();
    ui->labelY_id_d_d1511_6->clear();
    ui->labelY_id_d_d1511_5->clear();
    ui->labelY_id_d_d1511_4->clear();
    ui->labelY_id_d_d1511_3->clear();
    ui->labelY_id_d_d1511_2->clear();
    ui->labelY_id_d_d1511_1->clear();
    ui->labelY_id_d_d1511_2_15->clear();
    ui->labelY_id_d_d1511_2_14->clear();
    ui->labelY_id_d_d1511_2_13->clear();
    ui->labelY_id_d_d1511_2_12->clear();
    ui->labelY_id_d_d1511_2_11->clear();
    ui->labelY_id_d_d1511_2_10->clear();
    ui->labelY_id_d_d1511_2_9->clear();
    ui->labelY_id_d_d1511_2_8->clear();
    ui->labelY_id_d_d1511_2_7->clear();
    ui->labelY_id_d_d1511_2_6->clear();
    ui->labelY_id_d_d1511_2_5->clear();
    ui->labelY_id_d_d1511_2_4->clear();
    ui->labelY_id_d_d1511_2_3->clear();
    ui->labelY_id_d_d1511_2_2->clear();
    ui->labelY_id_d_d1511_2_1->clear();
    ui->labelX_d1511_errorIn->clear();
    ui->labelX_d1511_errorType->clear();
    ui->labelX_od_d_d1511_11->clear();
    ui->labelX_od_d_d1511_10->clear();
    ui->labelX_od_d_d1511_9->clear();
    ui->labelX_od_d_d1511_8->clear();
    ui->labelX_od_d_d1511_7->clear();
    ui->labelX_od_d_d1511_6->clear();
    ui->labelX_od_d_d1511_5->clear();
    ui->labelX_od_d_d1511_4->clear();
    ui->labelX_od_d_d1511_3->clear();
    ui->labelX_od_d_d1511_2->clear();
    ui->labelX_od_d_d1511_1->clear();
}
