#include "Include/studyform.h"
#include "ui_studyform.h"




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
    //wFlag = false;
    aFlag = false;
    //wGeometry = QRect();
    //sizeGrip = new QSizeGrip(this);
    //ui->gridLayout_9->addWidget(sizeGrip, ui->gridLayout_9->columnCount(), Qt::AlignBottom | Qt::AlignRight);
    inputFlag = NO_MODE;
    typeFlag = NO_TYPE;
    numberFlag = NO_SYSTEM;
    algFlag = NO_ALG;
    bitSeq = BitSequence();
    clearEncodedBitSeq = EncodedBitSequence();
    modEncodedBitSeq = EncodedBitSequence();
    bigInt = BigInteger();
    clearEncodedBigInt = EncodedBigInteger();
    modEncodedBigInt = EncodedBigInteger();
    ui->frame_6->setStackedWidget(ui->stackedWidget);
    ui->frame_4->setStackedWidget(ui->stackedWidget);
    ui->frame_5->setStackedWidget(ui->stackedWidget);
    ui->frame_7->setStackedWidget(ui->stackedWidget);
    ui->frame_9->setStackedWidget(ui->stackedWidget);
    ui->frame_10->setStackedWidget(ui->stackedWidget);
    ui->frame_12->setStackedWidget(ui->stackedWidget);
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        setBitsEncoding(ui->listWidget->count() - ui->listWidget->row(item) - 1);
    });
    connect(ui->listWidget_2, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        setBitsNoise(ui->listWidget_2->count() - ui->listWidget_2->row(item) - 1);
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
    if (event->button() == Qt::LeftButton /*&& !wFlag*/) {
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


//void StudyForm::mouseDoubleClickEvent(QMouseEvent *event) {
//    if (event->button() == Qt::LeftButton && event->y() < 30) {
//        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
//        animation->setDuration(500);
//        animation->setEasingCurve(QEasingCurve::InOutQuad);
//        animation->setStartValue(this->geometry());
//        //his->setUpdatesEnabled(false);
//        if (wFlag) {
//            animation->setEndValue(this->wGeometry);
//        } else {
//            this->wGeometry = this->geometry();
//            animation->setEndValue(QApplication::desktop()->availableGeometry());
//        }
//        connect(animation, &QPropertyAnimation::finished, this, [=]() {
//            //this->setUpdatesEnabled(true);
//            this->sizeGrip->setEnabled(wFlag);
//            this->wFlag ^=true;
//            delete animation;
//        });
//        animation->start();
//    }
//}


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
            inputFlag = MANUAL;
            ui->textEditData->setReadOnly(false);
        } else {
            inputFlag = NO_MODE;
            ui->textEditData->setReadOnly(true);
        }
        ui->spinBoxAmount->setReadOnly(true);
        ui->pushButtonAutoGen->setEnabled(false);
    } else if (senderSlider == ui->horizontalSliderFormInput_2) {
        ui->horizontalSliderFormInput_1->setValue(0);
        if(senderSlider->value() == 0) {
            inputFlag = GENERATED;
            ui->spinBoxAmount->setReadOnly(false);
            ui->pushButtonAutoGen->setEnabled(true);
        } else {
            inputFlag = NO_MODE;
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
    resetNS();
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderDataType_1) {
        ui->horizontalSliderDataType_2->setValue(0);
        if(senderSlider->value() == 0) {
            typeFlag = NUMERIC;
            setEnabledNS(true);
        } else {
            typeFlag = NO_TYPE;
            setEnabledNS(false);
        }
    } else if (senderSlider == ui->horizontalSliderDataType_2) {
        ui->horizontalSliderDataType_1->setValue(0);
        if(senderSlider->value() == 0) {
            typeFlag = TEXT;
            setEnabledNS(false);
        } else {
            typeFlag = NO_TYPE;
            setEnabledNS(false);
        }
    }
    bool enableFrame = senderSlider != ui->horizontalSliderDataType_2 ||
                       (senderSlider->value() == 1);
    if (enableFrame) {
        removeEffect(ui->frame_5);
        setShadow(ui->frame_5);
    } else {
        setBlur(ui->frame_5, BLUR_RADIUS_1);
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Выбор системы счисления".
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
            numberFlag = BINARY;
        else if (senderSlider == ui->horizontalSliderNS4)
            numberFlag = QUATERNARY;
        else if (senderSlider == ui->horizontalSliderNS8)
            numberFlag = OCTAL;
        else if (senderSlider == ui->horizontalSliderNS10)
            numberFlag = DECIMAL;
        else if (senderSlider == ui->horizontalSliderNS16)
            numberFlag = HEXADECIMAL;
    } else {
        numberFlag = NO_SYSTEM;
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
 * \details Обрабатывает нажатие кнопки выбора алгоритма кодирования.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushSliderEncoder_clicked() {
    resetData();
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
            algFlag = ALG_74;
        } else if(senderSlider == ui->horizontalSliderEncoder84) {
            algFlag = ALG_84;
        } else if(senderSlider == ui->horizontalSliderEncoder1511) {
            algFlag = ALG_1511;
        } else if(senderSlider == ui->horizontalSliderEncoder1611) {
            algFlag = ALG_1611;
        } else if(senderSlider == ui->horizontalSliderEncoder1511d) {
            algFlag = ALG_1511d;
        }
        ui->stackedWidget_2->setCurrentIndex(algFlag);
        ui->stackedWidget_3->setCurrentIndex(algFlag);
        ui->stackedWidget_4->setCurrentIndex(algFlag);
        if (algFlag == ALG_74 || algFlag == ALG_84) {
            ui->stackedWidget_5->setCurrentIndex(0);
        } else if(algFlag != NO_ALG) {
            ui->stackedWidget_5->setCurrentIndex(1);
        }
    } else {
        algFlag = NO_ALG;
    }
}


/*!
 * \brief Обработчик нажатия кнопки "Автоматическая генерация".
 * \details Обрабатывает нажатие кнопки автоматической генерации.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::on_pushButtonAutoGen_clicked() {
    switch (typeFlag) {
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
        switch(numberFlag) {
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
    if(typeFlag == NO_TYPE) {
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
        if(typeFlag == TEXT) {
            dataFlag = true;
            Converter::toBinary(bitSeq, data);
        } else {
            Converter::toBinary(bitSeq, data, numberFlag);
            switch (numberFlag) {
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
            switch (algFlag) {
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
    if(algFlag != ALG_1511d) {
        data = clearEncodedBitSeq[index].first.toString();
        encodedData = clearEncodedBitSeq[index].second.toString();
        switch (algFlag) {
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
void StudyForm::setBitsNoise(const int &index) {
    QString data, encodedData, modData;
    if(algFlag != ALG_1511d) {
        data = clearEncodedBitSeq[index].first.toString();
        encodedData = clearEncodedBitSeq[index].second.toString();
        modData = modEncodedBitSeq[index].second.toString();
        switch (algFlag) {
        case NO_ALG: {
            break;
        }
        case ALG_74: {
            /// \brief Установка значений во вкладке "Шум"
            ui->labelY_id_74_2_7->setText(encodedData.at(0));
            ui->labelY_id_74_2_6->setText(encodedData.at(1));
            ui->labelY_id_74_2_5->setText(encodedData.at(2));
            ui->labelY_id_74_2_4->setText(encodedData.at(3));
            ui->labelY_id_74_2_3->setText(encodedData.at(4));
            ui->labelY_id_74_2_2->setText(encodedData.at(5));
            ui->labelY_id_74_2_1->setText(encodedData.at(6));
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
            ui->labelY_id_84_2_8->setText(encodedData.at(0));
            ui->labelY_id_84_2_7->setText(encodedData.at(1));
            ui->labelY_id_84_2_6->setText(encodedData.at(2));
            ui->labelY_id_84_2_5->setText(encodedData.at(3));
            ui->labelY_id_84_2_4->setText(encodedData.at(4));
            ui->labelY_id_84_2_3->setText(encodedData.at(5));
            ui->labelY_id_84_2_2->setText(encodedData.at(6));
            ui->labelY_id_84_2_1->setText(encodedData.at(7));
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
    if (algFlag == ALG_74 || algFlag == ALG_84) {
        ui->labelX_d_74_2_4->setText(data.at(0));
        ui->labelX_d_74_2_3->setText(data.at(1));
        ui->labelX_d_74_2_2->setText(data.at(2));
        ui->labelX_d_74_2_1->setText(data.at(3));
    } else if (algFlag != NO_ALG) {
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


/*!
 * \brief Метод для сброса выбранного алгоритма.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetAlgo() {
    ui->horizontalSliderEncoder74->setValue(0);
    ui->horizontalSliderEncoder84->setValue(0);
    ui->horizontalSliderEncoder1511->setValue(0);
    ui->horizontalSliderEncoder1611->setValue(0);
    ui->horizontalSliderEncoder1511d->setValue(0);
    algFlag = NO_ALG;
}


/*!
 * \brief Метод для сброса выбранного алгоритма.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetNS() {
    ui->horizontalSliderNS2->setValue(0);
    ui->horizontalSliderNS4->setValue(0);
    ui->horizontalSliderNS8->setValue(0);
    ui->horizontalSliderNS10->setValue(0);
    ui->horizontalSliderNS16->setValue(0);
    numberFlag = NO_SYSTEM;
}


/*!
 * \brief Метод для включения/выключения выбора алгоритмов.
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
void StudyForm::resetPage74() {
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
void StudyForm::resetPage84() {
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
void StudyForm::resetPage1511() {
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
void StudyForm::resetPage1611() {
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
void StudyForm::resetPage1511d() {
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
void StudyForm::resetData() {
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    resetPage74();
    resetPage84();
    resetPage1511();
    resetPage1611();
    resetPage1511d();
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


