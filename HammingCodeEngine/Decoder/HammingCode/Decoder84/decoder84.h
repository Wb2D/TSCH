#ifndef DECODER84_H
#define DECODER84_H

#include <QPair>
#include <QVector>

#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"



/*!
 * \brief Класс Decoder84 реализует алгоритм декодирования кода Хэмминга (8,4).
 * \author Wb2D
 * \date 25 марта 2024
 * \details Этот класс декодирует закодированную битовую последовательность с использованием кода Хэмминга (8,4).
 * Процесс декодирования включает в себя выявление и исправление ошибок в закодированных данных. Алгоритм
 * декодирования кода Хэмминга (8,4) работает путем вычисления синдромов на основе проверочных бит и последующего
 * исправления ошибок.
*/

class Decoder84 {
public:
    static QPair<EncodedBitSequence, QVector<BitSequence>> start(const EncodedBitSequence &data);

private:
    static BitSequence decode(const BitSequence &data, BitSequence &result);
};

#endif //DECODER84_H
