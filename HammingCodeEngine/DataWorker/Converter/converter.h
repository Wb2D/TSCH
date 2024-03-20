#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include <QMap>
#include <QtMath>
#include <QDebug>

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"
#include "HammingCodeEngine/DataWorker/Converter/BigInteger\BigInteger.h"




/*!
 * \brief Класс Converter используется для перевода заданного числа в формате QString
 * в двоичную систему счисления и его перевода в объект класса BitSequence.
 * \author Wb2d.
 * \date 22 сентября 2023
 * \details Методы класса способны обрабатывать числа до 36-ричной системы счисления.
 * Для ускорения перевода и уменьшения вычислений используется словарь QMap<char, int>.
*/

class Converter {
public:
    static void toBinary(BitSequence &bitSequency, const QString &number, const int &base);

private:
    static BigInteger toDecimal(const QString &number, const int &base);
    static int charToDecimal(QChar ch);

    static const QMap<char, int> charToDigit; ///< словарь соответсвий
};


#endif // CONVERTER_H
