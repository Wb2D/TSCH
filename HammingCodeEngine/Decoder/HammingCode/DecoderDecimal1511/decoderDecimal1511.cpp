#include "HammingCodeEngine/Decoder/HammingCode/Decoder1511/decoder1511.h"




/*!
 * \brief Запускает процесс декодирования закодированной битовой последовательности с использованием кода Хэмминга (15, 11).
 * \param data Закодированная битовая последовательность для декодирования.
 * \return Пара, содержащая декодированную битовую последовательность и вектор синдромов.
*/
QPair<EncodedBitSequence, QVector<BitSequence>> Decoder1511::start(const EncodedBitSequence &data) {
    EncodedBitSequence result;
    QVector<BitSequence> syndroms;
    for (int i = 0; i < data.getAmount(); ++i) {
        BitSequence eData = data[i].second;
        BitSequence dData = BitSequence();
        syndroms.push_back(decode(eData, dData));
        result.addData(QPair<BitSequence, BitSequence>(dData, eData));
    }
    result.setMethod(3);
    result.setSize(15);
    return QPair<EncodedBitSequence, QVector<BitSequence>>(result, syndroms);
}


/*!
 * \brief Декодирует один блок закодированных данных, используя алгоритм декодирования кода Хэмминга (15, 11).
 * \param data Блок закодированных данных для декодирования.
 * \param result Декодированный блок данных.
 * \return Синдром ошибки, полученный во время декодирования.
*/
BitSequence Decoder1511::decode(const BitSequence &data, BitSequence &result) {
    BitSequence syndrome;
    syndrome.append(int(data[2] + data[4] + data[6] + data[8] +
            data[10] + data[12] + data[14] + data[0]) % 2);
    syndrome.append(int(data[2] + data[5] + data[6] + data[9] +
            data[10] + data[13] + data[14] + data[1]) % 2);
    syndrome.append(int(data[4] + data[5] + data[6] + data[11] +
            data[12] + data[13] + data[14] + data[3]) % 2);
    syndrome.append(int(data[8] + data[9] + data[10] + data[11] +
            data[12] + data[13] + data[14] + data[7]) % 2);
    int error = syndrome.toDecimal();
    result.append(data[2]);
    result.append(data[4]);
    result.append(data[5]);
    result.append(data[6]);
    result.append(data[8]);
    result.append(data[9]);
    result.append(data[10]);
    result.append(data[11]);
    result.append(data[12]);
    result.append(data[13]);
    result.append(data[14]);
    switch (error) {
    case 15:
        result.reverse(10);
        break;
    case 14:
        result.reverse(9);
        break;
    case 13:
        result.reverse(8);
        break;
    case 12:
        result.reverse(7);
        break;
    case 11:
        result.reverse(6);
        break;
    case 10:
        result.reverse(5);
        break;
    case 9:
        result.reverse(4);
        break;
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
