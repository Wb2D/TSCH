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
    dataFlag = NO_TYPE;
    numberFlag = NO_SYSTEM;
    algFlag = NO_ALG;
    bitSequence = BitSequence();
    encodedBitSequence = EncodedBitSequence();
    currentSubseq = -1;
    ui->frame_6->setStackedWidget(ui->stackedWidget);
    ui->frame_4->setStackedWidget(ui->stackedWidget);
    ui->frame_5->setStackedWidget(ui->stackedWidget);
    ui->frame_7->setStackedWidget(ui->stackedWidget);
    ui->frame_9->setStackedWidget(ui->stackedWidget);
    ui->frame_10->setStackedWidget(ui->stackedWidget);
    ui->frame_12->setStackedWidget(ui->stackedWidget);
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        int newSubseq = ui->listWidget->row(item);
        if(newSubseq != currentSubseq) {
            currentSubseq = newSubseq;
            setBits(encodedBitSequence[ui->listWidget->count() - newSubseq - 1]);
        }
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
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderDataType_1) {
        ui->horizontalSliderDataType_2->setValue(0);
        if(senderSlider->value() == 0) {
            dataFlag = NUMERIC;
            //ui->textEditData->clear();
        } else {
            dataFlag = NO_TYPE;
        }
    } else if (senderSlider == ui->horizontalSliderDataType_2) {
        ui->horizontalSliderDataType_1->setValue(0);
        if(senderSlider->value() == 0) {
            dataFlag = TEXT;
            //ui->textEditData->clear();
        } else {
            dataFlag = NO_TYPE;
        }
    }
    bool enableFrame = senderSlider != ui->horizontalSliderDataType_2 ||
                       (senderSlider->value() == 1);
    QList<QSlider*> sliders = { ui->horizontalSliderNS2,
                                ui->horizontalSliderNS4,
                                ui->horizontalSliderNS8,
                                ui->horizontalSliderNS10,
                                ui->horizontalSliderNS16, };
    for (QSlider *slider : sliders) {
        if (slider != senderSlider) {
            slider->setEnabled(enableFrame);
        }
    }
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
    if(senderSlider->value() == 0) {
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
    for(QSlider *slider : sliders) {
        if(slider != senderSlider) {
            slider->setValue(0);
        }
    }
    if(!senderSlider->value()) {
        if(senderSlider == ui->horizontalSliderEncoder74) {
            ui->stackedWidget_2->setCurrentIndex(0);
            algFlag = ALG_74;
        } else if(senderSlider == ui->horizontalSliderEncoder84) {
            ui->stackedWidget_2->setCurrentIndex(1);
            algFlag = ALG_84;
        } else if(senderSlider == ui->horizontalSliderEncoder1511) {
            ui->stackedWidget_2->setCurrentIndex(2);
            algFlag = ALG_1511;
        } else if(senderSlider == ui->horizontalSliderEncoder1611) {
            ui->stackedWidget_2->setCurrentIndex(3);
            algFlag = ALG_1611;
        } else if(senderSlider == ui->horizontalSliderEncoder1511d) {
            ui->stackedWidget_2->setCurrentIndex(4);\
            algFlag = ALG_1511d;
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
    switch (dataFlag) {
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
        /// \todo Добавить сюда генерацию текста, когда реализую
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
    switch (dataFlag) {
    case NO_TYPE: {
        NotificationForm *notification = new NotificationForm("Кодирование невозможна. Выберите тип данных.");
        this->setEnabled(false);
        notification->show();
        QObject::connect(notification, &NotificationForm::finished, this, [=]() {
            notification->deleteLater();
            this->setEnabled(true);
        });
        break;
    }
    case TEXT: {
        /// \todo Добавить сюда генерацию текста, когда реализую
        break;
    }
    case NUMERIC: {
        QString data = ui->textEditData->toPlainText();
        bool dataFlag = false;
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

        }
        }
        if(dataFlag) {
            /// \todo на этом моменте нужно сделать проверку с десятичным алгоритмом кодирования
            Converter::toBinary(bitSequence, data, numberFlag);
            switch (algFlag) {
            case NO_ALG: {
                NotificationForm *notification = new NotificationForm("Кодирование невозможно. "
                                                                      "Выберите алгоритм. ");
                this->setEnabled(false);
                notification->show();
                QObject::connect(notification, &NotificationForm::finished, this, [=]() {
                    notification->deleteLater();
                    this->setEnabled(true);
                });
                break;
            }
            case ALG_74: {
                setListSeq(4, bitSequence);
                encodedBitSequence = Encoder74::start(bitSequence);
                break;
            }
            case ALG_84: {
                setListSeq(4, bitSequence);
                encodedBitSequence = Encoder84::start(bitSequence);
                break;
            }
            case ALG_1511: {
                setListSeq(11, bitSequence);
                encodedBitSequence = Encoder1511::start(bitSequence);
                break;
            }
            case ALG_1611: {
                setListSeq(11, bitSequence);
                encodedBitSequence = Encoder1611::start(bitSequence);
                break;
            }
            case ALG_1511d: {
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
        break;
    }
    }
}


/*!
 * \brief Метод для установки содержимого списка с последовательностями бит.
 * \param size Длина битовой последовательности.
 * \return Отсутствуют.
*/
void StudyForm::setListSeq(const int &size, const BitSequence &data) {
    ui->listWidget->clear();
    int eSize = data.length();
    if (eSize % size) {
        eSize += size - (eSize % size);
    }
    for(int i = eSize; i > 0; i -= size) {
        ui->listWidget->addItem(data.subsequence(i - size, i - 1).toString());
    }
}


/*!
 * \brief Метод для установки содержимого списка с последовательностями бит.
 * \param size Длина битовой последовательности.
 * \return Отсутствуют.
*/
void StudyForm::setBits(const QPair<BitSequence, BitSequence> &bits) {
    QString bitSeq = bits.first.toString();
    QString encodedBitSeq = bits.second.toString();
    switch (algFlag) {
    case NO_ALG: {
        break;
    }
    case ALG_74: {
        ui->labelX_id_74_4->setText(bitSeq.at(0));
        ui->labelX_id_74_3->setText(bitSeq.at(1));
        ui->labelX_id_74_2->setText(bitSeq.at(2));
        ui->labelX_id_74_1->setText(bitSeq.at(3));
        ui->labelY_od_74_7->setText(encodedBitSeq.at(0));
        ui->labelY_od_74_6->setText(encodedBitSeq.at(1));
        ui->labelY_od_74_5->setText(encodedBitSeq.at(2));
        ui->labelY_od_74_4->setText(encodedBitSeq.at(3));
        ui->labelY_od_74_3->setText(encodedBitSeq.at(4));
        ui->labelY_od_74_2->setText(encodedBitSeq.at(5));
        ui->labelY_od_74_1->setText(encodedBitSeq.at(6));
        break;
    }
    case ALG_84: {
        ui->labelX_id_84_4->setText(bitSeq.at(0));
        ui->labelX_id_84_3->setText(bitSeq.at(1));
        ui->labelX_id_84_2->setText(bitSeq.at(2));
        ui->labelX_id_84_1->setText(bitSeq.at(3));
        ui->labelY_od_84_8->setText(encodedBitSeq.at(0));
        ui->labelY_od_84_7->setText(encodedBitSeq.at(1));
        ui->labelY_od_84_6->setText(encodedBitSeq.at(2));
        ui->labelY_od_84_5->setText(encodedBitSeq.at(3));
        ui->labelY_od_84_4->setText(encodedBitSeq.at(4));
        ui->labelY_od_84_3->setText(encodedBitSeq.at(5));
        ui->labelY_od_84_2->setText(encodedBitSeq.at(6));
        ui->labelY_od_84_1->setText(encodedBitSeq.at(7));
        break;
    }
    case ALG_1511: {
        ui->labelX_id_1511_11->setText(bitSeq.at(0));
        ui->labelX_id_1511_10->setText(bitSeq.at(1));
        ui->labelX_id_1511_9->setText(bitSeq.at(2));
        ui->labelX_id_1511_8->setText(bitSeq.at(3));
        ui->labelX_id_1511_7->setText(bitSeq.at(4));
        ui->labelX_id_1511_6->setText(bitSeq.at(5));
        ui->labelX_id_1511_5->setText(bitSeq.at(6));
        ui->labelX_id_1511_4->setText(bitSeq.at(7));
        ui->labelX_id_1511_3->setText(bitSeq.at(8));
        ui->labelX_id_1511_2->setText(bitSeq.at(9));
        ui->labelX_id_1511_1->setText(bitSeq.at(10));
        ui->labelY_id_1511_15->setText(encodedBitSeq.at(0));
        ui->labelY_id_1511_14->setText(encodedBitSeq.at(1));
        ui->labelY_id_1511_13->setText(encodedBitSeq.at(2));
        ui->labelY_id_1511_12->setText(encodedBitSeq.at(3));
        ui->labelY_id_1511_11->setText(encodedBitSeq.at(4));
        ui->labelY_id_1511_10->setText(encodedBitSeq.at(5));
        ui->labelY_id_1511_9->setText(encodedBitSeq.at(6));
        ui->labelY_id_1511_8->setText(encodedBitSeq.at(7));
        ui->labelY_id_1511_7->setText(encodedBitSeq.at(8));
        ui->labelY_id_1511_6->setText(encodedBitSeq.at(9));
        ui->labelY_id_1511_5->setText(encodedBitSeq.at(10));
        ui->labelY_id_1511_4->setText(encodedBitSeq.at(11));
        ui->labelY_id_1511_3->setText(encodedBitSeq.at(12));
        ui->labelY_id_1511_2->setText(encodedBitSeq.at(13));
        ui->labelY_id_1511_1->setText(encodedBitSeq.at(14));
        break;
    }
    case ALG_1611: {
        ui->labelX_id_1611_11->setText(bitSeq.at(0));
        ui->labelX_id_1611_10->setText(bitSeq.at(1));
        ui->labelX_id_1611_9->setText(bitSeq.at(2));
        ui->labelX_id_1611_8->setText(bitSeq.at(3));
        ui->labelX_id_1611_7->setText(bitSeq.at(3));
        ui->labelX_id_1611_6->setText(bitSeq.at(3));
        ui->labelX_id_1611_5->setText(bitSeq.at(3));
        ui->labelX_id_1611_4->setText(bitSeq.at(3));
        ui->labelX_id_1611_3->setText(bitSeq.at(3));
        ui->labelX_id_1611_2->setText(bitSeq.at(3));
        ui->labelX_id_1611_1->setText(bitSeq.at(3));
        ui->labelY_id_1611_16->setText(encodedBitSeq.at(0));
        ui->labelY_id_1611_15->setText(encodedBitSeq.at(1));
        ui->labelY_id_1611_14->setText(encodedBitSeq.at(2));
        ui->labelY_id_1611_13->setText(encodedBitSeq.at(3));
        ui->labelY_id_1611_12->setText(encodedBitSeq.at(4));
        ui->labelY_id_1611_11->setText(encodedBitSeq.at(5));
        ui->labelY_id_1611_10->setText(encodedBitSeq.at(6));
        ui->labelY_id_1611_9->setText(encodedBitSeq.at(7));
        ui->labelY_id_1611_8->setText(encodedBitSeq.at(8));
        ui->labelY_id_1611_7->setText(encodedBitSeq.at(9));
        ui->labelY_id_1611_6->setText(encodedBitSeq.at(10));
        ui->labelY_id_1611_5->setText(encodedBitSeq.at(11));
        ui->labelY_id_1611_4->setText(encodedBitSeq.at(12));
        ui->labelY_id_1611_3->setText(encodedBitSeq.at(13));
        ui->labelY_id_1611_2->setText(encodedBitSeq.at(14));
        ui->labelY_id_1611_1->setText(encodedBitSeq.at(15));
        break;
    }
    default: {
        /// \todo здесь прописать другие алгоритмы
        break;
    }
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
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 7-4
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
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 8-4
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
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 15-11
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
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 16-11
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
}


/*!
 * \brief Метод для сброса содержимого вкладки кодирования алгоритмом 15-11d
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetPage1511d() {

}


/*!
 * \brief Метод для сброса содержимого всех вкладов кодирования
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void StudyForm::resetData() {
    ui->listWidget->clear();
    resetPage74();
    resetPage84();
    resetPage1511();
    resetPage1611();
    resetPage1511d();
}
