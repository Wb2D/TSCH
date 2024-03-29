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
#include <QList>
#include <QTimer>

#include "Include/notificationform.h"
#include "Include/clickableLabel.h"

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"
#include "HammingCodeEngine/DataWorker/BitSequence/BitSequenceShell/bitSequenceShell.h"
#include "HammingCodeEngine/DataWorker/BigInteger/BigInteger.h"
#include "HammingCodeEngine/DataWorker/BigInteger/BigIntegerShell/bigIntegerShell.h"
#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/NumberGenerator/numberGenerator.h"

#include "HammingCodeEngine/Encoder/HammingCode/Encoder74/Encoder74.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder84/encoder84.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder1511/encoder1511.h"
#include "HammingCodeEngine/Encoder/HammingCode/Encoder1611/encoder1611.h"
#include "HammingCodeEngine/Encoder/HammingCode/EncoderDecimal1511/encoderDecimal1511.h"

#include "HammingCodeEngine/Decoder/HammingCode/Decoder74/decoder74.h"
#include "HammingCodeEngine/Decoder/HammingCode/Decoder84/decoder84.h"
#include "HammingCodeEngine/Decoder/HammingCode/Decoder1511/decoder1511.h"
#include "HammingCodeEngine/Decoder/HammingCode/Decoder1611/decoder1611.h"
#include "HammingCodeEngine/Decoder/HammingCode/DecoderDecimal1511/decoderDecimal1511.h"




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
    void on_pushButtonEncoding_clicked();
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
    /// \brief Слоты для вкладки Шум.
    void on_pushButtonNoise_clicked();
    void on_pushSliderFormInputNoise_clicked();
    void on_pushSliderErrorType_clicled();
    void on_pushSliderUseTo_clicked();
    void on_pushButtonAutoNoise_clicked();
    void onDataLabel_doubleClicked();
    /// \brief Слоты для вкладки Декодирование.
    void on_pushButtonDecoding_clicked();
    void on_pushButtonCopyData_clicked();
    void on_pushButtonDecode_clicked();
    void on_pushSliderDataType_2_clicked();
    void on_pushSliderNS_2_clicked();
    void on_pushSliderDecoder_clicked();

private:
    void setShadow(QWidget*);
    void setBlur(QWidget*, int);
    void removeEffect(QWidget*);
    void setListSeq(const int&, const BitSequence&, QListWidget*);
    void setListInt(const int&, const BigInteger&, QListWidget*);
    void setBitsEncoding(const int&);
    void setBitsNoise(const int&, const bool&);
    void resetAlgo();
    void resetPageEncoder74();
    void resetPageEncoder84();
    void resetPageEncoder1511();
    void resetPageEncoder1611();
    void resetPageEncoder1511d();
    void resetEncoderData();
    void resetEncoderNS();
    void resetLabelXd11();
    void resetLabelXd4();
    void setEnabledNS(const bool&);
    void autoError(const bool&, const int&, const int&);
    void setBitsDecoding(const int&);
    void setEnabledNS_2(const bool&);
    void resetEncoderNS_2();
    void resetAlgo_2();
    void resetPageDecoder74();
    void resetPageDecoder84();
    void resetPageDecoder1511();
    void resetPageDecoder1611();
    void resetPageDecoder1511d();
    void resetDecoderData();

    static const QRegularExpression LEADING_REGEX;
    static const QRegularExpression BINARY_REGEX;
    static const QRegularExpression QUATERNARY_REGEX;
    static const QRegularExpression OCTAL_REGEX;
    static const QRegularExpression DECIMAL_REGEX;
    static const QRegularExpression HEXADECIMAL_REGEX;

    enum InputType {
        NO_MODE,
        MANUAL,
        GENERATED,
    } encodeInputFlag, noiseInputFlag;

    enum DataType {
        NO_TYPE,
        TEXT,
        NUMERIC,
    } encodeTypeFlag, decodeTypeFlag;

    enum NumberSystem {
        NO_SYSTEM,
        BINARY = 2,
        QUATERNARY = 4,
        OCTAL = 8,
        DECIMAL = 10,
        HEXADECIMAL = 16,
    } encodeNumberFlag, decodeNumberFlag;

    enum Algorithm {
        NO_ALG = -1,
        ALG_74,
        ALG_84,
        ALG_1511,
        ALG_1611,
        ALG_1511d,
    } encodeAlgFlag, decodeAlgFlag;

    enum ErrorType {
        NO_ERR,
        SINGLE,
        DOUBLE,
    } noiseErrorFlag;

    enum ErrorImpact {
        NO_IMPACT,
        TO_ALL,
        TO_CUSTOM,
    } noiseImpactFlag;

    Ui::StudyForm *ui;
    QPoint mPosition;
    bool aFlag;
    BitSequence bitSeq;
    BitSequenceShell clearEncodedBitSeq;
    BitSequenceShell modEncodedBitSeq;
    BigInteger bigInt;
    BigIntegerShell clearEncodedBigInt;
    BigIntegerShell modEncodedBigInt;
    QPair<BitSequenceShell, QVector<BitSequence>> decodedBitData;
    QPair<BigIntegerShell, QVector<BigInteger>> decodedIntData;
    static const int BLUR_RADIUS_1 = 8;
    static const int BLUR_RADIUS_2 = 4;
};


#endif // STUDYFORM_H
