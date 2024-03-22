#ifndef STUDYFORM_H
#define STUDYFORM_H

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpression>
#include <QPair>
//#include <QSizeGrip>

#include "Include/notificationform.h"
#include "Include/clickableLabel.h"

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"
#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"
#include "HammingCodeEngine/DataWorker/Converter/BigInteger/BigInteger.h"
#include "HammingCodeEngine/DataWorker/Converter/BigInteger/EncodedBigInteger/encodedBigInteger.h"
#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/NumberGenerator/numberGenerator.h"

#include "HammingCodeEngine/Encoder/HammingCode/Encoder74/Encoder74.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder84/encoder84.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder1511/encoder1511.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder1611/encoder1611.h"
#include "HammingCodeEngine/Encoder/HammingCode/EncoderDecimal1511/encoderDecimal1511.h"




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
    /// \brief Слоты для вкладки Кодирование.
    void on_pushButtonClose_clicked();
    void on_pushButtonMinimize_clicked();
    void on_pushSliderFormInput_clicked();
    void on_pushSliderDataType_clicked();
    void on_pushSliderNS_clicked();
    void on_pushSliderEncoder_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonClose_2_clicked();
    void on_pushButtonAutoGen_clicked();
    void on_pushButtonEncode_clicked();
    void on_pushButtonEncoding_clicked();
    void on_pushButtonNoise_clicked();
    /// \brief Слоты для вкладки Шум.
    void on_pushSliderFormInputNoise_clicked();
    void on_pushSliderErrorType_clicled();
    void on_pushSliderUseTo_clicked();
    void on_pushButtonAutoNoise_clicked();
    void onDataLabel_doubleClicked();

private:
    void setShadow(QWidget*);
    void setBlur(QWidget*, int);
    void removeEffect(QWidget*);
    void setListSeq(const int&, const BitSequence&, QListWidget*);
    void setListInt(const int&, const BigInteger&, QListWidget*);
    void setBitsEncoding(const int&);
    void setBitsNoise(const int&);
    void resetAlgo();
    void resetPage74();
    void resetPage84();
    void resetPage1511();
    void resetPage1611();
    void resetPage1511d();
    void resetData();
    void resetNS();
    void resetLabelXd11();
    void resetLabelXd4();
    void setEnabledNS(const bool&);

    static const QRegularExpression BINARY_REGEX;
    static const QRegularExpression QUATERNARY_REGEX;
    static const QRegularExpression OCTAL_REGEX;
    static const QRegularExpression DECIMAL_REGEX;
    static const QRegularExpression HEXADECIMAL_REGEX;

    enum InputType {
        NO_MODE,
        MANUAL,
        GENERATED,
    } inputFlag, noiseFlag;

    enum DataType {
        NO_TYPE,
        TEXT,
        NUMERIC,
    } typeFlag;

    enum NumberSystem {
        NO_SYSTEM,
        BINARY = 2,
        QUATERNARY = 4,
        OCTAL = 8,
        DECIMAL = 10,
        HEXADECIMAL = 16,
    } numberFlag;

    enum Algorithm {
        NO_ALG = -1,
        ALG_74,
        ALG_84,
        ALG_1511,
        ALG_1611,
        ALG_1511d,
    } algFlag;

    enum ErrorType {
        NO_ERR,
        SINGLE,
        DOUBLE,
    } errorFlag;

    enum ErrorImpact {
        NO_IMPACT,
        TO_ALL,
        TO_CUSTOM,
    } impactFlag;

    Ui::StudyForm *ui;
    //QSizeGrip *sizeGrip;
    QPoint mPosition;
    //bool wFlag;
    bool aFlag;
    BitSequence bitSeq;
    EncodedBitSequence clearEncodedBitSeq;
    EncodedBitSequence modEncodedBitSeq;
    BigInteger bigInt;
    EncodedBigInteger clearEncodedBigInt;
    EncodedBigInteger modEncodedBigInt;
    //EncodedBigInteger e
    //QRect wGeometry;
    static const int BLUR_RADIUS_1 = 8;
    static const int BLUR_RADIUS_2 = 4;
};


#endif // STUDYFORM_H
