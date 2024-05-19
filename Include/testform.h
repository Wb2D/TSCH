#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QMouseEvent>
#include <QTime>

#include "Include/askiihelper.h"

#include "HammingCodeEngine/DataWorker/NumberGenerator/numberGenerator.h"
#include "HammingCodeEngine/DataWorker/Converter/converter.h"

#include "HammingCodeEngine/Encoder/HammingCode/Encoder74/Encoder74.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder84/encoder84.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder1511/encoder1511.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder1611/encoder1611.h"

#include "HammingCodeEngine/Decoder/HammingCode/Decoder1511/decoder1511.h"
#include "HammingCodeEngine/Decoder/HammingCode/Decoder1611/decoder1611.h"




namespace Ui {
class TestForm;
}



class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr);
    ~TestForm();

    void setStatus(const QString&);
    void setUser(const QString&);

signals:
    void closed();
    void exited();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private slots:
    void on_pushButtonMinimize_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonClose_2_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonResult_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::TestForm *ui;
    AskiiHelper *askiiHelper;

    QPoint mPosition;
    bool aFlag;
    QString answer1;
    QString answer2;
    QString answer3;

    QTime startTime;

    static const QString TRUE_ANS;
    static const QString WRONG_ANS;
};


#endif // TESTFORM_H
