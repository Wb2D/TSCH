#include "Include/studyform.h"
#include "ui_studyform.h"

StudyForm::StudyForm(QWidget *parent) :
    QWidget(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::StudyForm) {
    ui->setupUi(this);
    setWindowOpacity(0.98);     // прозрачность окна
    mPosition = QPoint();
}

StudyForm::~StudyForm() {
    delete ui;
}

void StudyForm::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Проверяем, был ли клик в верхней части окна (например, в пределах заголовка)
        if (event->y() < 30) {
            mPosition = event->globalPos() - frameGeometry().topLeft();
        }
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
        ui->frame_5->setGraphicsEffect(nullptr);
    } else {
        QGraphicsBlurEffect *effect = new QGraphicsBlurEffect(ui->frame_5);
        effect->setBlurRadius(6); // радиус размытия
        effect->setBlurHints(QGraphicsBlurEffect::QualityHint); // нацепил сглаживание
        ui->frame_5->setGraphicsEffect(effect);
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


