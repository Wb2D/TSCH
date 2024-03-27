#ifndef DECODERDECIMAL1511_H
#define DECODERDECIMAL1511_H

#include <QPair>
#include <QVector>

#include "HammingCodeEngine/DataWorker/Converter/converter.h"
#include "HammingCodeEngine/DataWorker/BigInteger/BigIntegerShell/bigIntegerShell.h"



/*!
 * \brief Класс Decoder74 реализует алгоритм декодирования кода Хэмминга (15, 11).
 * \author Wb2D
 * \date 26 марта 2024
 * \details Этот класс декодирует закодированную битовую последовательность с использованием кода Хэмминга (15, 11).
 * Процесс декодирования включает в себя выявление и исправление ошибок в закодированных данных. Алгоритм
 * декодирования кода Хэмминга (15, 11) работает путем вычисления синдромов на основе проверочных бит и последующего
 * исправления ошибок.
*/

class DecoderDecimal1511 {
public:
    static QPair<BigIntegerShell, QVector<BigInteger>> start(const BigIntegerShell &data);

private:
    static BigInteger decode(const BigInteger &data, BigInteger &result);
};

#endif //DECODERDECIMAL1511_H
