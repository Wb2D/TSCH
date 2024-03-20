#ifndef ENCODEDBIGINTEGER_H
#define ENCODEDBIGINTEGER_H

#include "HammingCodeEngine/DataWorker/Converter/BigInteger/BigInteger.h"




/*!
 * \brief Класс EncodedBigInteger является оберткой для закодированного числа BigInteger.
 * \author Wb2D.
 * \date 23 сентября 2023
 * \details Этот класс включает информацию о закодированном числе, используемом в методе 
 * кодирования, времени, затраченном на кодирование, и количестве частей, на которые была 
 * разбита исходная последовательность.
*/

class EncodedBigInteger {
public:
    EncodedBigInteger(const BigInteger &digit, const QString &method, const qint64 &time,
                      const int &iteration) : digit(digit), method(method), time(time),
                      iteration(iteration) {    }
    const BigInteger &getData() const { return digit; }
    const QString &getMethod() const { return method; }
    const qint64 &getTime() const { return time; }
    const int &getIteration() const { return iteration; }
    const QString toString() const;

private:
    BigInteger digit;
    QString method;
    qint64 time;
    int iteration;
};


#endif // ENCODEDBIGINTEGER_H
