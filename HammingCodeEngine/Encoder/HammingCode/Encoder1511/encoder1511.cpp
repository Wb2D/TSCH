#include "HammingCodeEngine/Encoder/HammingCode/Encoder1511/encoder1511.h"



/*!
 * \brief Метод запускает кодирование битовой последовательности с использованием
 * кода Хэмминга (15,11).
 * \param data Исходная битовая последовательность.
 * \return Закодированная битовая последовательность.
*/
EncodedBitSequence Encoder1511:: start(const BitSequence &data) {
    EncodedBitSequence result;
    int eSize = data.length();
    if (eSize % 11) {
        eSize += 11  - (eSize % 11);
    }
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < eSize; i += 11) {
        BitSequence bitSeq = data.subsequence(i, i + 10);
        BitSequence eData = BitSequence();
        encode(bitSeq, eData);
        result.addData(QPair<BitSequence, BitSequence>(bitSeq, eData));
    }
    result.setTime(timer.elapsed());
    result.setMethod(3);
    result.setIteration(eSize / 11);
    return result;
}


/*!
 * \brief Метод осуществляет кодирование четырех битов в восемь битов по алгоритму (15,11) Хэмминга.
 * \param data Одиннадцать исходных бит для кодирования.
 * \param result Результат кодирования (Пятнадцать бит).
*/
void Encoder1511::encode(const BitSequence &data, BitSequence &result) {
    result.append(int(data[0] + data[1] + data[3] + data[4] + data[6] + data[8] + data[10]) % 2);
    result.append(int(data[0] + data[2] + data[3] + data[5] + data[6] + data[9] + data[10]) % 2);
    result.append(data[0]);
    result.append(int(data[1] + data[2] + data[3] + data[7] + data[8] + data[9] + data[10]) % 2);
    result.append(data[1]);
    result.append(data[2]);
    result.append(data[3]);
    result.append(int(data[4] + data[5] + data[6] + data[7] + data[8] + data[9] + data[10]) % 2);
    result.append(data[4]);
    result.append(data[5]);
    result.append(data[6]);
    result.append(data[7]);
    result.append(data[8]);
    result.append(data[9]);
    result.append(data[10]);
}
