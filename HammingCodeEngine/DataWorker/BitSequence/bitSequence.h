#ifndef BITSEQUENCE_H
#define BITSEQUENCE_H

#include <QDebug>
#include <QString>

#include "HammingCodeEngine/DataWorker/BigInteger/BigInteger.h"




/*!
 * \brief Класс BitSequence предназначен для хранения битовой последовательности
 * и обеспечивает доступ к каждому биту по его индексу.
 * \author Wb2D
 * \date 22 сентября 2023
 * \details Данный класс предоставляет возможность установки и получения битов,
 * а также увеличивает размер последовательности при необходимости с помощью DynamicResize.
 * Каждый бит хранится отдельно, что обеспечивает удобный доступ к ним.
*/

class BitSequence {
public:
    BitSequence() : bitArray(NULL), bitCount(0), arraySize(0) {}
    BitSequence(const QString&);
    BitSequence(const BitSequence&);
    BitSequence& operator=(const BitSequence&);
    ~BitSequence();

    int length() const { return bitCount; }
    bool operator[](const int&) const;
    void reverse(const int&);
    void set(const int&, const bool&);
    void append(const bool&);
    void append(const BitSequence&);
    QString toString() const;
    int toDecimal() const;
    BigInteger toBigInt() const;
    BitSequence subsequence(int, int) const;

private:
    void resize(const int& length);

    bool *bitArray; ///< битовая последовательность
    int bitCount; ///< число установленных бит
    int arraySize; ///< возможное число бит
};


#endif // BITSEQUENCE_H
