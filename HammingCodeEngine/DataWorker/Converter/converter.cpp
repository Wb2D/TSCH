#include "HammingCodeEngine\DataWorker\Converter\converter.h"




const QMap<char, int> Converter::charToDigit = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11},
    {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}, {'G', 16}, {'H', 17},
    {'I', 18}, {'J', 19}, {'K', 20}, {'L', 21}, {'M', 22}, {'N', 23},
    {'O', 24}, {'P', 25}, {'Q', 26}, {'R', 27}, {'S', 28}, {'T', 29},
    {'U', 30}, {'V', 31}, {'W', 32}, {'X', 33}, {'Y', 34}, {'Z', 35},
};


/*!
 * \brief Метод переводит число в формате строки в десятичную систему счисления.
 * \param number Число в формате строки.
 * \param base Основание системы счисления исходного числа.
 * \return Число в десятичной системе счисления в формате BigInteger.
*/
 BigInteger Converter::toDecimal(const QString &number, const int &base) {
    BigInteger result("0");
    BigInteger value("1");
    for (int i = number.length() - 1; i >= 0; --i) {
        int tmp = charToDecimal(number.at(i));
        if (tmp == -1 || tmp >= base) {
            qDebug() << "ERROR : Converter -> toDecimal";
            return BigInteger("0");
        }
        result = result + (BigInteger(QString::number(tmp)) * value);
        value = value * BigInteger(QString::number(base));
    }
    return result;
}


/*!
 * \brief Метод переводит символ числа в десятичную систему счисления на основе словаря.
 * \param ch Символ числа.
 * \return Число в десятичной системе счисления.
*/
int Converter::charToDecimal(const QChar &ch) {
    int result = -1;
    if(ch.isDigit()) {
        return ch.digitValue();
    } else if(ch.isLetter()) {
        result = charToDigit.value(ch.toUpper().toLatin1());
    }
    return result;
}


/*!
 * \brief Метод конвертирует число в двоичную систему счисления.
 * \param bitSequence Последовательность битов, в которую будет записан результат.
 * \param number Число в формате строки.
 * \param base Основание системы счисления исходного числа.
 * \return Отсутствуют.
*/
void Converter::toBinary(BitSequence &bitSequency, const QString &number, const int &base) {
    bitSequency = BitSequence();
    if (base < 2 || base > 36) {
        qDebug() << "ERROR : Converter -> wrong base";
    }
    BigInteger decimalNumber = toDecimal(number, base);
    while(!decimalNumber.isZero()) {
        bitSequency.append((decimalNumber.isEven()));
        decimalNumber = decimalNumber.div2();
    }
}


/*!
 * \brief Переводит число из указанной системы счисления в четверичную систему счисления.
 * \param number Число в исходной системе счисления.
 * \param base Основание исходной системы счисления.
 * \return Представление числа в формате строки.
*/
QString Converter::toQuaternary(const QString &number, const int &base) {
    QString result;
    if (base < 2 || base > 36) {
        qDebug() << "ERROR : Converter -> wrong base";
    }
    BigInteger decimalNumber = toDecimal(number, base);
    while(!decimalNumber.isZero()) {
        int remainder = 0;
        decimalNumber = decimalNumber.div4(remainder);
        result.push_front(charToDigit.key(remainder));
    }
    return result;
}


/*!
 * \brief Переводит число из указанной системы счисления в восьмеричную систему счисления.
 * \param number Число в исходной системе счисления.
 * \param base Основание исходной системы счисления.
 * \return Представление числа в формате строки.
*/
QString Converter::toOctal(const QString &number, const int &base) {
    QString result;
    if (base < 2 || base > 36) {
        qDebug() << "ERROR : Converter -> wrong base";
    }
    BigInteger decimalNumber = toDecimal(number, base);
    while(!decimalNumber.isZero()) {
        int remainder = 0;
        decimalNumber = decimalNumber.div8(remainder);
        result.push_front(charToDigit.key(remainder));
    }
    return result;
}


/*!
 * \brief Переводит число из указанной системы счисления в шестнадцатеричную систему счисления.
 * \param number Число в исходной системе счисления.
 * \param base Основание исходной системы счисления.
 * \return Представление числа в формате строки.
*/
QString Converter::toHexadecimal(const QString &number, const int &base) {
    QString result;
    if (base < 2 || base > 36) {
        qDebug() << "ERROR : Converter -> wrong base";
    }
    BigInteger decimalNumber = toDecimal(number, base);
    while(!decimalNumber.isZero()) {
        int remainder = 0;
        decimalNumber = decimalNumber.div16(remainder);
        result.push_front(charToDigit.key(remainder));
    }
    return result;
}


/*!
 * \brief Переводит битовую последовательность в восьмеричную текст.
 * \param data Исходная битовая последовательность.
 * \return Полученный текст в формате строки.
*/
QString Converter::toText(const QString &data) {
    QString binary = data;
    while(binary.length() % 8) {
        binary.push_front("0");
    }
    QString result;
    for (int i = 0; i < binary.size(); i += 8) {
        QString byte = binary.mid(i, 8);
        bool flag;
        char character = static_cast<char>(byte.toInt(&flag, 2));
        if (flag) {
            result.append(character);
        } else {
            return QString();
        }
    }
    return result;
}


/*!
 * \brief Метод конвертирует текст в двоичное представление.
 * \param bitSequence Последовательность битов, в которую будет записан результат.
 * \param text Входной текст.
 * \return Отсутствуют.
*/
void Converter::toBinary(BitSequence &bitSequency, const QString &text) {
    bitSequency = BitSequence();
    for (int i = text.length() - 1; i >= 0; --i) {
        bitSequency.append(charToByte(text.at(i)));
    }
}


/*!
 * \brief Метод конвертирует символ в двоичное представление.
 * \param ch Символ текста.
 * \return Двоичное представление.
*/
BitSequence Converter::charToByte(const QChar &ch) {
    BitSequence asciiCode;
    Converter::toBinary(asciiCode, QString::number(ch.toLatin1()), 10);
    while(asciiCode.length() != 8) {
        asciiCode.append(false);
    }
    return asciiCode;
}
