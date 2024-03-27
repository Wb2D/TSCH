#include "HammingCodeEngine/Decoder/HammingCode/Decoder74/decoder74.h"




/*!
 * \brief Запускает процесс декодирования закодированной битовой последовательности с использованием кода Хэмминга (7,4).
 * \param data Закодированная битовая последовательность для декодирования.
 * \return Пара, содержащая декодированную битовую последовательность и вектор синдромов.
*/
QPair<BitSequenceShell, QVector<BitSequence>> Decoder74::start(const BitSequenceShell &data) {
    BitSequenceShell result;
    QVector<BitSequence> syndroms;
    for (int i = 0; i < data.getAmount(); ++i) {
        BitSequence eData = data[i].second;
        BitSequence dData = BitSequence();
        syndroms.push_back(decode(eData, dData));
        result.addData(QPair<BitSequence, BitSequence>(dData, eData));
    }
    result.setMethod(1);
    result.setSize(7);
    return QPair<BitSequenceShell, QVector<BitSequence>>(result, syndroms);
}


/*!
 * \brief Декодирует один блок закодированных данных, используя алгоритм декодирования кода Хэмминга (7,4).
 * \param data Блок закодированных данных для декодирования.
 * \param result Декодированный блок данных.
 * \return Синдром ошибки, полученный во время декодирования.
*/
BitSequence Decoder74::decode(const BitSequence &data, BitSequence &result) {
    BitSequence syndrome;
    syndrome.append(int(data[2] + data[4] + data[6] + data[0]) % 2);
    syndrome.append(int(data[2] + data[5] + data[6] + data[1]) % 2);
    syndrome.append(int(data[4] + data[5] + data[6] + data[3]) % 2);
    int error = syndrome.toDecimal();
    result.append(data[2]);
    result.append(data[4]);
    result.append(data[5]);
    result.append(data[6]);
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
