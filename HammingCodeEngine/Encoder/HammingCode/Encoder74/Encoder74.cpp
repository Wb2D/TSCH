#include "HammingCodeEngine/Encoder/HammingCode/Encoder74/Encoder74.h"




/*!
 * \brief Метод запускает кодирование битовой последовательности с использованием
 * кода Хэмминга (7,4).
 * \param data Исходная битовая последовательность.
 * \return Закодированная битовая последовательность.
*/
EncodedBitSequence Encoder74::start(const BitSequence &data) {
    EncodedBitSequence result;
    int eSize = data.length();
    if (eSize % 4) {
        eSize += 4 - (eSize % 4);
    }
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < eSize; i += 4) {
        BitSequence bitSeq = data.subsequence(i, i + 3);
        BitSequence eData = BitSequence();
        encode(bitSeq, eData);
        result.addData(QPair<BitSequence, BitSequence>(bitSeq, eData));
    }
    result.setTime(timer.elapsed());
    result.setMethod(1);
    result.setIteration(eSize / 4);
    return result;
}


/*!
 * \brief Метод осуществляет кодирование четырех битов в семь битов по алгоритму (7,4) Хэмминга.
 * \param data Четыре исходных бита для кодирования.
 * \param result Результат кодирования (семь битов).
*/
void Encoder74::encode(const BitSequence &data, BitSequence &result) {
    result.append(int(data[0] + data[1] + data[3]) % 2);
    result.append(int(data[0] + data[2] + data[3]) % 2);
    result.append(data[0]);
    result.append(int(data[1] + data[2] + data[3]) % 2);
    result.append(data[1]);
    result.append(data[2]);
    result.append(data[3]);
}
