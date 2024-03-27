#ifndef DECODER1611_H
#define DECODER1611_H

#include <QPair>
#include <QVector>

#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/BitSequence/BitSequenceShell/bitSequenceShell.h"



/*!
 * \brief Класс Decoder1611 реализует алгоритм декодирования кода Хэмминга (16, 11).
 * \author Wb2D
 * \date 26 марта 2024
 * \details Этот класс декодирует закодированную битовую последовательность с использованием кода Хэмминга (16,11).
 * Процесс декодирования включает в себя выявление и исправление ошибок в закодированных данных. Алгоритм
 * декодирования кода Хэмминга (16, 11) работает путем вычисления синдромов на основе проверочных бит и последующего
 * исправления ошибок.
*/

class Decoder1611 {
public:
    static QPair<BitSequenceShell, QVector<BitSequence>> start(const BitSequenceShell &data);

private:
    static BitSequence decode(const BitSequence &data, BitSequence &result);
};

#endif //DECODER1611_H
