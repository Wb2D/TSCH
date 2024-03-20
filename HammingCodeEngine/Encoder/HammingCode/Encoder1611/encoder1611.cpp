#include "HammingCodeEngine/Encoder/HammingCode/Encoder1611/encoder1611.h"




/*!
 * \brief Метод запускает кодирование битовой последовательности с использованием
 * кода Хэмминга (16,11).
 * \param data Исходная битовая последовательность.
 * \return Закодированная битовая последовательность.
*/
EncodedBitSequence Encoder1611:: start(const BitSequence &data) {
    BitSequence eData;
    int eSize = data.length();
    if (eSize % 11) {
        eSize += 11  - (eSize % 11);
    }
    for (int i = 0; i < eSize; i += 11) {
        encode(data.subsequence(i, i + 10), eData);
    }
    return EncodedBitSequence(eData, "H1611", 0, eSize / 11);
}


/*!
 * \brief Метод осуществляет кодирование четырех битов в восемь битов по алгоритму (16,11) Хэмминга.
 * \param data Одиннадцать исходных бит для кодирования.
 * \param result Результат кодирования (Шестнадцать бит).
*/
void Encoder1611::encode(const BitSequence &data, BitSequence &result) {
    bool e1 = int(data[0] +data[1] + data[3] + data[4] + data[6] + data[8] + data[10]) % 2;
    bool e2 = int(data[0] + data[2] + data[3] + data[5] + data[6] + data[9] + data[10]) % 2;
    bool e3 = int(data[1] + data[2] + data[3] + data[7] + data[8] + data[9] + data[10]) % 2;
    bool e4 = int(data[4] + data[5] + data[6] + data[7] + data[8] + data[9] + data[10]) % 2;

    result.append(int(e1 + e2 + e3 + e4 +data[0] +data[1] + data[2] + data[3] + data[4] + data[5] +
            data[6] + data[7] + data[8] + data[9] + data[10]) % 2);
    result.append(e1);
    result.append(e2);
    result.append(data[0]);
    result.append(e3);
    result.append(data[1]);
    result.append(data[2]);
    result.append(data[3]);
    result.append(e4);
    result.append(data[4]);
    result.append(data[5]);
    result.append(data[6]);
    result.append(data[7]);
    result.append(data[8]);
    result.append(data[9]);
    result.append(data[10]);
}
