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
    EncodedBigInteger() : data(), method(0), iteration(0) {     }
    EncodedBigInteger(const QVector<QPair<BigInteger, BigInteger>> &data, const int &method,
                      const int &iteration) : data(data), method(method), iteration(iteration) {    }
    EncodedBigInteger(const EncodedBigInteger &obj)
        : data(obj.data), method(obj.method), iteration(obj.iteration) {    }
    const QPair<BigInteger, BigInteger>& operator[](int index) const { return data[index]; }
    EncodedBigInteger& operator=(const EncodedBigInteger&);
    void addData(const QPair<BigInteger, BigInteger> &pair) { data.push_back(pair); }
    void setData(const QVector<QPair<BigInteger, BigInteger>> &data) { this->data = data; }
    const QVector<QPair<BigInteger, BigInteger>> &getData() const { return data; }
    void setMethod(const int &method) { this->method = method; }
    const int &getMethod() const { return method; }
    void setIteration(const int &iteration) { this->iteration = iteration; }
    const int &getIteration() const { return iteration; }

private:
    QVector<QPair<BigInteger, BigInteger>> data;
    int method;
    int iteration;
};


#endif // ENCODEDBIGINTEGER_H
