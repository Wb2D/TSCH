#include "Include/studyform.h"
#include "ui_studyform.h"


StudyForm::StudyForm(QWidget *parent) :
    QWidget(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::StudyForm) {
    ui->setupUi(this);
    setWindowOpacity(0.98); // прозрачность окна
    mPosition = QPoint();
    wFlag = false;
    aFlag = false;
    wGeometry = QRect();
    sizeGrip = new QSizeGrip(this);
    ui->gridLayout_9->addWidget(sizeGrip, ui->gridLayout_9->columnCount(), Qt::AlignBottom | Qt::AlignRight);
    ui->frame_6->setStackedWidget(ui->stackedWidget);
    ui->frame_4->setStackedWidget(ui->stackedWidget);
    ui->frame_5->setStackedWidget(ui->stackedWidget);
    ui->frame_7->setStackedWidget(ui->stackedWidget);
    ui->frame_9->setStackedWidget(ui->stackedWidget);
    ui->frame_10->setStackedWidget(ui->stackedWidget);
    ui->frame_12->setStackedWidget(ui->stackedWidget);

    // ЗАРАНЕЕ ПРЕДУСМАТРИВАЮ МЕТОД ДЛЯ ЗАПОЛНЕНИЯ (НАДЕЮСЬ, ЧТО НЕ ЗАБУДУ)
    connect(ui->listWidget, &QListWidget::itemClicked, [=](QListWidgetItem *item){
        qDebug() << "Clicked on item:" << item->text(); // элемент, по которому был совершен клик
    });
}


StudyForm::~StudyForm() { delete ui; }


// метод установки тени
void StudyForm::setShadow(QWidget *widget) {
    QGraphicsDropShadowEffect *shEffect = new QGraphicsDropShadowEffect();
    shEffect->setOffset(0, 0);
    shEffect->setColor(QColor(255, 255, 255, 155));
    shEffect->setBlurRadius(15);
    widget->setGraphicsEffect(shEffect);
}


// метод установки блюра
void StudyForm::setBlur(QWidget *widget, int blurRadius) {
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect(widget);
    effect->setBlurRadius(blurRadius);
    effect->setBlurHints(QGraphicsBlurEffect::AnimationHint); // нацепил сглаживание
    widget->setGraphicsEffect(effect);
}


// метод удаления блюра
void StudyForm::removeEffect(QWidget *widget) {
    delete widget->graphicsEffect();
    widget->setGraphicsEffect(nullptr);
}


void StudyForm::mousePressEvent(QMouseEvent *event) {
    event->ignore();
    if (event->button() == Qt::LeftButton && !wFlag) {
        if (event->y() < 30 && event->x() < this->width() - 120) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
            aFlag = true;
        } else {
            aFlag = false;
        }
        this->setFocus();
    }
}


void StudyForm::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (event->buttons() & Qt::LeftButton && aFlag) {
        //  переместить окно только если захвачена НУЖНА часть окна
            move(event->globalPos() - mPosition);
    }
}


void StudyForm::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        aFlag = false; // cброс флага части окна
    }
}


void StudyForm::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->y() < 30) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(500);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->setStartValue(this->geometry());
        //his->setUpdatesEnabled(false);
        if (wFlag) {
            animation->setEndValue(this->wGeometry);
        } else {
            this->wGeometry = this->geometry();
            animation->setEndValue(QApplication::desktop()->availableGeometry());
        }
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            //this->setUpdatesEnabled(true);
            this->sizeGrip->setEnabled(wFlag);
            this->wFlag ^=true;
            delete animation;
        });
        animation->start();
    }
}


// свернуть окно
void StudyForm::on_pushButtonMinimize_clicked() {
    this->showMinimized();
}


// закрыть окно
void StudyForm::on_pushButtonClose_clicked() {
    this->close();
}


// выбор формы ввода данных
void StudyForm::on_pushSliderFormInput_clicked() {
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderFormInput_1) {
        ui->horizontalSliderFormInput_2->setValue(0);
    } else if (senderSlider == ui->horizontalSliderFormInput_2) {
        ui->horizontalSliderFormInput_1->setValue(0);
    }
    bool enableButton = senderSlider == ui->horizontalSliderFormInput_2 ||
            (senderSlider == ui->horizontalSliderFormInput_1 && senderSlider->value() != 0);
    ui->frame_8->setEnabled(enableButton);
    ui->pushButtonAutoGen->setEnabled(enableButton);
    ui->textEditData->setReadOnly(enableButton);
    ui->spinBoxAmount->setReadOnly(!enableButton);
    if(enableButton) {
        removeEffect(ui->frame_8);
    } else {
        setBlur(ui->frame_8, BLUR_RADIUS_2);
    }
    ui->frame_8->update();
}


// выбор типа входных данных
void StudyForm::on_pushSliderDataType_clicked() {
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (senderSlider == ui->horizontalSliderDataType_1) {
        ui->horizontalSliderDataType_2->setValue(0);
    } else if (senderSlider == ui->horizontalSliderDataType_2) {
        ui->horizontalSliderDataType_1->setValue(0);
    }
    bool enableFrame = senderSlider != ui->horizontalSliderDataType_2 ||
                       (senderSlider->value() == 1);
    QList<QSlider*> sliders = { ui->horizontalSliderNS2,
                                ui->horizontalSliderNS4,
                                ui->horizontalSliderNS8,
                                ui->horizontalSliderNS10,
                                ui->horizontalSliderNS16, };
    // включаю или выключаю слайдеры
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


// выбор системы счисления для числовой информации
void StudyForm::on_pushSliderNS_clicked() {
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
    bool enableFrame = senderSlider == ui->horizontalSliderNS10 || senderSlider->value() == 1;
    ui->horizontalSliderEncoder1511d->setEnabled(enableFrame);
    if(enableFrame) {
        removeEffect(ui->frame_11);
    } else {
        setBlur(ui->frame_11, BLUR_RADIUS_1);
    }
    ui->frame_11->update();
}


// выбор алгоритма кодирования
void StudyForm::on_pushSliderEncoder_clicked() {
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
        } else if(senderSlider == ui->horizontalSliderEncoder84) {
            ui->stackedWidget_2->setCurrentIndex(1);
        } else if(senderSlider == ui->horizontalSliderEncoder1511) {
            ui->stackedWidget_2->setCurrentIndex(2);
        } else if(senderSlider == ui->horizontalSliderEncoder1611) {
            ui->stackedWidget_2->setCurrentIndex(3);
        } else if(senderSlider == ui->horizontalSliderEncoder1511d) {
            ui->stackedWidget_2->setCurrentIndex(4);
        }
    }
}
