#include "Include/studyform.h"
#include "ui_studyform.h"

StudyForm::StudyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudyForm)
{
    ui->setupUi(this);
}

StudyForm::~StudyForm()
{
    delete ui;
}


void StudyForm::on_pushButton_1_clicked()
{
    this->close();
    emit openMainWindow();
}

