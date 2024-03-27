#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <QVector>
#include <QtGlobal>
#include <QString>
#include <QDebug>

#include "HammingCodeEngine/DataWorker/NumberGenerator/numberGenerator.h"



/*!
 * \brief Класс BigInteger реализует длинную арифметику для работы с большими натуральными 
 * числами.
 * \author Wb2D.
 * \date 22 сентября 2023
 * \details Этот класс предоставляет функции для выполнения арифметических операций,
 * таких как сложение и умножение, а также проверок на четность и нулевое значение числа.
*/

class BigInteger {
public:
    BigInteger() { }
    BigInteger(QString number);

    QString toString() const;
    BigInteger div2() const;
    BigInteger div4(int&) const;
    BigInteger div8(int&) const;
    BigInteger div16(int&) const;
    BigInteger operator+(const BigInteger &number) const;
    BigInteger operator*(const BigInteger &number) const;
    bool isEven() const;
    bool isZero() const;
    void append(const int &digit);
    int operator[](const int& index) const;
    int length() const;
    BigInteger subdigit(const int &from, const int &to) const;
    void distort(const int&);

private:
    void removeZeros();

    QVector<int> data; ///< вектор для хранения числа
};


#endif // BIGINTEGER_H
