#include "Include/studyform.h"
#include "ui_studyform.h"


StudyForm::StudyForm(QWidget *parent) :
    QWidget(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::StudyForm) {
    ui->setupUi(this);
    setWindowOpacity(0.98);     // прозрачность окна
    mPosition = QPoint();
    //ui->gridLayout->addWidget(new QSizeGrip(this), ui->gridLayout->columnCount(), Qt::AlignBottom | Qt::AlignRight);
    setShadow(ui->frame_6);
    setShadow(ui->frame_4);
    setShadow(ui->frame_5);
    setShadow(ui->frame_7);
}

StudyForm::~StudyForm() {
    delete ui->frame_6->graphicsEffect();
    delete ui->frame_4->graphicsEffect();
    delete ui->frame_5->graphicsEffect();
    delete ui->frame_7->graphicsEffect();
    delete ui;
}

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
    if (event->button() == Qt::LeftButton) {
        // Проверяем, был ли клик в верхней части окна (например, в пределах заголовка)
        if (event->y() < 30) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
        }
        this->setFocus();
    }
}


void StudyForm::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // Перемещаем окно только если захвачена верхняя часть
        if (event->y() < 30) {
            move(event->globalPos() - mPosition);
            event->accept();
        }
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
    bool enableFrame = senderSlider == ui->horizontalSliderDataType_1 ||
                       (senderSlider == ui->horizontalSliderDataType_2 && senderSlider->value() != 0);
    ui->frame_5->setEnabled(enableFrame);
    if (enableFrame) {
        removeEffect(ui->frame_5);
        setShadow(ui->frame_5);
    } else {
        setBlur(ui->frame_5, BLUR_RADIUS_1);
    }
    ui->frame_5->setStyleSheet(ui->frame_5->styleSheet());
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
}


