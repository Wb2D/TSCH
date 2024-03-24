#ifndef DECODER74_H
#define DECODER74_H

#include <QPair>
#include <QVector>

#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"



/*!
 * \brief Класс Decoder74 реализует алгоритм декодирования кода Хэмминга (7,4).
 * \author Wb2D
 * \date 24 марта 2024
 * \details Этот класс декодирует закодированную битовую последовательность с использованием кода Хэмминга (7,4).
 * Процесс декодирования включает в себя выявление и исправление ошибок в закодированных данных. Алгоритм
 * декодирования кода Хэмминга (7,4) работает путем вычисления синдромов на основе проверочных бит и последующего
 * исправления ошибок.
*/

class Decoder74 {
public:
    static QPair<EncodedBitSequence, QVector<int>> start(const EncodedBitSequence &data);

private:
    static int decode(const BitSequence &data, BitSequence &result);
};

#endif //DECODER74_H
