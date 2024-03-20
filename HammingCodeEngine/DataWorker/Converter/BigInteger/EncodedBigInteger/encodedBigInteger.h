#ifndef ENCODEDBIGINTEGER_H
#define ENCODEDBIGINTEGER_H

#include <QDateTime>
#include <QVector>
#include <QPair>
#include <QString>

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
    EncodedBigInteger() : data(), method(0), time(0), iteration(0) {}
    EncodedBigInteger(const QVector<QPair<BigInteger, BigInteger>> &data, const int &method, const qint64 &time,
                      const int &iteration) : data(data), method(method), time(time),
                      iteration(iteration) {    }
    EncodedBigInteger(const EncodedBigInteger &obj)
        : data(obj.data), method(obj.method), time(obj.time), iteration(obj.iteration) {    }
    EncodedBigInteger& operator=(const EncodedBigInteger&);
    const QVector<QPair<BigInteger, BigInteger>> &getData() const { return data; }
    const int &getMethod() const { return method; }
    const qint64 &getTime() const { return time; }
    const int &getIteration() const { return iteration; }
    const QString toString() const;

private:
    QVector<QPair<BigInteger, BigInteger>> data;
    int method;
    qint64 time;
    int iteration;
};


#endif // ENCODEDBIGINTEGER_H
