#ifndef STUDYFORM_H
#define STUDYFORM_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsBlurEffect>
#include <QSizeGrip>


namespace Ui {
class StudyForm;
}

class StudyForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudyForm(QWidget *parent = nullptr);
    ~StudyForm();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;


private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushSliderFormInput_clicked();
    void on_pushSliderDataType_clicked();
    void on_pushSliderNS_clicked();

private:
    Ui::StudyForm *ui;
    QPoint mPosition;
};

#endif // STUDYFORM_H
