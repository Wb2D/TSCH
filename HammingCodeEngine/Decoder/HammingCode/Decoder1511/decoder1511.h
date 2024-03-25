#ifndef DECODER1511_H
#define DECODER1511_H

#include <QPair>
#include <QVector>

#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"



/*!
 * \brief Класс Decoder74 реализует алгоритм декодирования кода Хэмминга (15, 11).
 * \author Wb2D
 * \date 25 марта 2024
 * \details Этот класс декодирует закодированную битовую последовательность с использованием кода Хэмминга (15, 11).
 * Процесс декодирования включает в себя выявление и исправление ошибок в закодированных данных. Алгоритм
 * декодирования кода Хэмминга (15, 11) работает путем вычисления синдромов на основе проверочных бит и последующего
 * исправления ошибок.
*/

class Decoder1511 {
public:
    static QPair<EncodedBitSequence, QVector<BitSequence>> start(const EncodedBitSequence &data);

private:
    static BitSequence decode(const BitSequence &data, BitSequence &result);
};

#endif //DECODER1511_H