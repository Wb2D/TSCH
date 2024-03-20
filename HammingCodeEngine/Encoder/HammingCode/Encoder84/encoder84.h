#ifndef ENCODER84_H
#define ENCODER84_H

#include <QElapsedTimer>
#include <QPair>

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"
#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"



 
/*!
 * \brief Класс Encoder84 реализует алгоритм перевода последовательности бит в код Хэмминга 8-4.
 * \author Wb2D
 * \date 2 октября 2023
 * \details Данный класс разбивает битовую последовательность на части и кодирует каждую часть
 * по алгоритму кода Хэмминга 8-4. В случае, если размерность превышает 4, последовательность 
 * будет разбита на несколько подпоследовательностей.
 * Код Хэмминга 8-4 составляется по следующему принципу:
 * e1 e2 d1 e3 d2 d3 d4, где d1, d2, d3, d4 - элементы битовой последовательности
 * e0 = (e1 + e2 + d1 + e3 + d2 + d3 + d4 + d5 + d6 + d7) mod2
 * e1 = (d3 + d5 + d7) mod2
 * e2 = (d3 + d6 + d7) mod2
 * e3 = (d5 + d6 + d7) mod2
 * Примечание: при необходимости добавить недостающие биты, незначащий нуль добавляется
 * в правую часть, т.к последовательность инвертирована.
*/

class Encoder84 {
public:
    static EncodedBitSequence start(const BitSequence &data);

private:
    static void encode(const BitSequence &data, BitSequence &result);
};


#endif // ENCODER84_H
