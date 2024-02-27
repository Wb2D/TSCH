#ifndef STUDYFORM_H
#define STUDYFORM_H

#include <QWidget>

namespace Ui {
class StudyForm;
}

class StudyForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudyForm(QWidget *parent = nullptr);
    ~StudyForm();

signals:
    void openMainWindow(); // сигнал для mainwindow на открытие

private slots:
    void on_pushButton_1_clicked();

private:
    Ui::StudyForm *ui;
};

#endif // STUDYFORM_H
