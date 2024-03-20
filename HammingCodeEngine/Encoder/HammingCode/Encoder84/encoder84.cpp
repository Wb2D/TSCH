#include "HammingCodeEngine/Encoder/HammingCode/Encoder84/encoder84.h"




/*!
 * \brief Метод запускает кодирование битовой последовательности с использованием
 * кода Хэмминга (8,4).
 * \param data Исходная битовая последовательность.
 * \return Закодированная битовая последовательность.
*/
EncodedBitSequence Encoder84::start(const BitSequence &data) {
   EncodedBitSequence result;
    int eSize = data.length();
    if (eSize % 4) {
        eSize += 4 - (eSize % 4);
    }
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < eSize; i +=4) {
        BitSequence bitSeq = data.subsequence(i, i + 3);
        BitSequence eData = BitSequence();
        encode(bitSeq, eData);
        result.addData(QPair<BitSequence, BitSequence>(bitSeq, eData));
    }
    result.setTime(timer.elapsed());
    result.setMethod(2);
    result.setIteration(eSize / 4);
    return result;
}


/*!
 * \brief Метод осуществляет кодирование четырех битов в восемь битов по алгоритму (8,4) Хэмминга.
 * \param data Четыре исходных бита для кодирования.
 * \param result Результат кодирования (восемь битов).
*/
void Encoder84::encode(const BitSequence &data, BitSequence &result) {
    bool e1 = int(data[0] + data[1] + data[3]) % 2;
    bool e2 = int(data[0] + data[2] + data[3]) % 2;
    bool e3 = int(data[1] + data[2] + data[3]) % 2;

    result.append(int(e1 + e2 +e3 + data[0] + data[1] + data[2] + data[3]));
    result.append(e1);
    result.append(e2);
    result.append(data[0]);
    result.append(e3);
    result.append(data[1]);
    result.append(data[2]);
    result.append(data[3]);
}
