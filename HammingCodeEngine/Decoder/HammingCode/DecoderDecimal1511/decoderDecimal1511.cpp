#include "HammingCodeEngine/Decoder/HammingCode/DecoderDecimal1511/decoderDecimal1511.h"




/*!
 * \brief Запускает процесс декодирования закодированной числовой последовательности с использованием
 * кода Хэмминга (15, 11).
 * \param data Закодированная битовая последовательность для декодирования.
 * \return Пара, содержащая декодированную битовую последовательность и вектор синдромов.
*/
QPair<EncodedBigInteger, QVector<BigInteger>> DecoderDecimal1511::start(const EncodedBigInteger &data) {
    EncodedBigInteger result;
    QVector<BigInteger> syndroms;
    for (int i = 0; i < data.getAmount(); ++i) {
        BigInteger eData = data[i].second;
        BigInteger dData = BigInteger();
        syndroms.push_back(decode(eData, dData));
        result.addData(QPair<BigInteger, BigInteger>(dData, eData));
    }
    result.setMethod(4);
    result.setSize(15);
    return QPair<EncodedBigInteger, QVector<BigInteger>>(result, syndroms);
}


/*!
 * \brief Декодирует один блок закодированных данных, используя алгоритм декодирования кода
 * Хэмминга (15, 11) для десятичных чисел.
 * \param data Блок закодированных данных для декодирования.
 * \param result Декодированный блок данных.
 * \return Синдром ошибки, полученный во время декодирования.
*/
BigInteger DecoderDecimal1511::decode(const BigInteger &data, BigInteger &result) {
    BigInteger syndrome;
    BitSequence index;
    int e1 = (data[2] + data[4] + data[6] + data[8] + data[10] + data[12] + data[14] + data[0]) % 10;
    syndrome.append(e1);
    index.append(e1 > 0);
    int e2 = (data[2] + data[5] + data[6] + data[9] + data[10] + data[13] + data[14] + data[1]) % 10;
    syndrome.append(e2);
    index.append(e2 > 0);
    int e3 = (data[4] + data[5] + data[6] + data[11] + data[12] + data[13] + data[14] + data[3]) % 10;
    syndrome.append(e3);
    index.append(e3 > 0);
    int e4 = (data[8] + data[9] + data[10] + data[11] + data[12] + data[13] + data[14] + data[7]) % 10;
    syndrome.append(e4);
    index.append(e4 > 0);
    int error = index.toDecimal();
    result.append(error == 3 ? data[2] : (data[2] - e2) % 10);
    result.append(error == 5 ? data[4] : (data[4] - e3) % 10);
    result.append(error == 6 ? data[5] : (data[5] - e3) % 10);
    result.append(error == 7 ? data[6] : (data[6] - e3) % 10);
    result.append(error == 9 ? data[8] : (data[8] - e3) % 10);
    result.append(error == 10 ? data[9] : (data[9] - e4) % 10);
    result.append(error == 11 ? data[10] : (data[10] - e4) % 10);
    result.append(error == 12 ? data[11] : (data[11] - e4) % 10);
    result.append(error == 13 ? data[12] : (data[12] - e4) % 10);
    result.append(error == 14 ? data[13] : (data[13] - e4) % 10);
    result.append(error == 15 ? data[14] : (data[14] - e4) % 10);
    return syndrome;
}
