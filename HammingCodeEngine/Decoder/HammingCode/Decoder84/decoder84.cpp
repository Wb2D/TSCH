#include "HammingCodeEngine/Decoder/HammingCode/Decoder84/decoder84.h"




/*!
 * \brief Запускает процесс декодирования закодированной битовой последовательности с использованием кода Хэмминга (8,4).
 * \param data Закодированная битовая последовательность для декодирования.
 * \return Пара, содержащая декодированную битовую последовательность и вектор синдромов.
*/
QPair<EncodedBitSequence, QVector<BitSequence>> Decoder84::start(const EncodedBitSequence &data) {
    EncodedBitSequence result;
    QVector<BitSequence> syndroms;
    for (int i = 0; i < data.getAmount(); ++i) {
        BitSequence eData = data[i].second;
        BitSequence dData = BitSequence();
        syndroms.push_back(decode(eData, dData));
        result.addData(QPair<BitSequence, BitSequence>(dData, eData));
    }
    result.setMethod(2);
    result.setSize(8);
    return QPair<EncodedBitSequence, QVector<BitSequence>>(result, syndroms);
}


/*!
 * \brief Декодирует один блок закодированных данных, используя алгоритм декодирования кода Хэмминга (8,4).
 * \param data Блок закодированных данных для декодирования.
 * \param result Декодированный блок данных.
 * \return Синдром ошибки, полученный во время декодирования.
*/
BitSequence Decoder84::decode(const BitSequence &data, BitSequence &result) {
    BitSequence syndrome;
    syndrome.append(int(data[0] + data[1] + data[2] + data[3] + data[4] +
            data[5] + data[6] + data[7]) % 2);
    syndrome.append(int(data[3] + data[5] + data[7] + data[1]) % 2);
    syndrome.append(int(data[3] + data[6] + data[7] + data[2]) % 2);
    syndrome.append(int(data[5] + data[6] + data[7] + data[4]) % 2);
    int error = syndrome.subsequence(1, 3).toDecimal();
    result.append(data[3]);
    result.append(data[5]);
    result.append(data[6]);
    result.append(data[7]);
    switch (error) {
    case 7:
        result.reverse(3);
        break;
    case 6:
        result.reverse(2);
        break;
    case 5:
        result.reverse(1);
        break;
    case 3:
        result.reverse(0);
        break;
    default:
        break;
    }
    return syndrome;
}
