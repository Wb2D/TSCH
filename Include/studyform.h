#ifndef STUDYFORM_H
#define STUDYFORM_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
//#include <QSizeGrip>




namespace Ui {
class StudyForm;
}

/*!
 * \brief Класс StudyForm предназначен для предоставления оператору интерфейса обучающего режима.
 * \author Wb2D.
 * \date 29 февраля 2024
 * \details Класс StudyForm реализует функционал обучения, предоставляемый системой пользователю.
 * Это окно обеспечивает возможности по кодированию, декодированию и добавлению ошибок, а также
 * дает максимально наглядную информацию о процессе.
 * Основные возможности:
 * - кодирование данных;
 * - декодирование данных;
 * - добавление ошибки;
 * - подробное отображение информации о процессе;
 * - вкладки для настройки параметров (шума, типа данных, и т. д.);
 * - кнопки для возврата и выхода из приложения.
 * \todo Вкладки шума, декодирования. Кнопки для возврата и выхода.
*/

class StudyForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudyForm(QWidget *parent = nullptr);
    ~StudyForm();

    void setStatus(const QString&);
    void setUser(const QString&);

signals:
    void closed();
    void exited();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    //void mouseDoubleClickEvent(QMouseEvent*) override;

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushSliderFormInput_clicked();
    void on_pushSliderDataType_clicked();
    void on_pushSliderNS_clicked();
    void on_pushSliderEncoder_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonClose_2_clicked();

private:
    void setShadow(QWidget*);
    void setBlur(QWidget*, int);
    void removeEffect(QWidget*);

    Ui::StudyForm *ui;
    //QSizeGrip *sizeGrip;
    QPoint mPosition;
    //bool wFlag;
    bool aFlag;
    //QRect wGeometry;
    static const int BLUR_RADIUS_1 = 8;
    static const int BLUR_RADIUS_2 = 4;
};


#endif // STUDYFORM_H
