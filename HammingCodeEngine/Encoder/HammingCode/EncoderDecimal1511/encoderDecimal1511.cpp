#include "HammingCodeEngine/Encoder/HammingCode/EncoderDecimal1511/encoderDecimal1511.h"




/*!
 * \brief Метод запускает кодирование битовой последовательности с использованием
 * кода Хэмминга (15,11) для десятичных цифр числа.
 * \param data Исходная битовая последовательность.
 * \return Закодированная битовая последовательность.
*/
EncodedBigInteger EncoderDecimal1511::start(const BigInteger &data) {
    EncodedBigInteger result;
    int eSize = data.length();
    if (eSize % 11) {
        eSize += 11 - (eSize % 11);
    }
    for (int i = 0; i < eSize; i += 11) {
        BigInteger bigInteger = data.subdigit(i, i + 10);
        BigInteger encodedBigInt;
        encode(bigInteger, encodedBigInt);
        result.addData(QPair<BigInteger, BigInteger>(bigInteger, encodedBigInt));
    }
    result.setMethod(5);
    result.setIteration(eSize / 11);
    return result;
}


/*!
 * \brief Метод осуществляет кодирование четырех битов в восемь битов по алгоритму (15,11) Хэмминга.
 * \param data Одиннадцать исходных бит для кодирования.
 * \param result Результат кодирования (Пятнадцать бит).
*/
void EncoderDecimal1511::encode(const BigInteger &data, BigInteger &result) {
    result.append((10 - (int(data[0] +data[1] + data[3] + data[4] + data[6] + data[8] + data[10]) % 10)) % 10);
    result.append((10 - (int(data[0] + data[2] + data[3] + data[5] + data[6] + data[9] + data[10]) % 10)) % 10);
    result.append(data[0]);
    result.append((10 - (int(data[1] + data[2] + data[3] + data[7] + data[8] + data[9] + data[10])) % 10) % 10);
    result.append(data[1]);
    result.append(data[2]);
    result.append(data[3]);
    result.append((10 - (int(data[4] + data[5] + data[6] + data[7] + data[8] + data[9] + data[10]) % 10)) % 10);
    result.append(data[4]);
    result.append(data[5]);
    result.append(data[6]);
    result.append(data[7]);
    result.append(data[8]);
    result.append(data[9]);
    result.append(data[10]);
}
