#ifndef BigIntegerShell_H
#define BigIntegerShell_H

#include <QDateTime>
#include <QVector>
#include <QPair>
#include <QString>

#include "HammingCodeEngine/DataWorker/BigInteger/BigInteger.h"




/*!
 * \brief Класс BigIntegerShell является оберткой для закодированного числа BigInteger.
 * \author Wb2D.
 * \date 23 сентября 2023
 * \details Этот класс включает информацию о закодированном числе, используемом в методе 
 * кодирования, времени, затраченном на кодирование, и количестве частей, на которые была 
 * разбита исходная последовательность.
*/

class BigIntegerShell {
public:
    BigIntegerShell() : data(), method(0), size(0) {     }
    BigIntegerShell(const BigInteger&, const int&, const int&, const bool&);
    BigIntegerShell(const QVector<QPair<BigInteger, BigInteger>> &data, const int &method,
                      const int &size) : data(data), method(method), size(size) {    }
    BigIntegerShell(const BigIntegerShell &obj)
        : data(obj.data), method(obj.method), size(obj.size) {    }
    BigIntegerShell& operator=(const BigIntegerShell&);
    const QPair<BigInteger, BigInteger>& operator[](int index) const { return data[index]; }
    void addData(const QPair<BigInteger, BigInteger> &pair) { data.push_back(pair); }
    void setData(const QVector<QPair<BigInteger, BigInteger>> &data) { this->data = data; }
    const QVector<QPair<BigInteger, BigInteger>> &getData() const { return data; }
    void setMethod(const int &method) { this->method = method; }
    const int &getMethod() const { return method; }
    void setSize(const int &size) { this->size = size; }
    const int &getSize() const { return size; }
    int getAmount() const { return data.length(); }
    void addError(const int&, const int&);

    QString getFirst() const;
    QString getSecond() const;

private:
    QVector<QPair<BigInteger, BigInteger>> data;
    int method;
    int size;
};


#endif // BigIntegerShell_H
