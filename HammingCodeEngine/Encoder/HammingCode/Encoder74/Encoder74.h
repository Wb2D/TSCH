#ifndef ENCODER74_H
#define ENCODER74_H

#include <QElapsedTimer>
#include <QPair>

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"
#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"




/*!
 * \brief Класс Encoder74 реализует алгоритм перевода последовательности бит в код Хэмминга 7-4.
 * \author Wb2D
 * \date 2 октября 2023
 * \details Данный класс разбивает битовую последовательность на части и кодирует каждую часть
 * по алгоритму кода Хэмминга 7-4. В случае, если размерность превышает 4, последовательность 
 * будет разбита на несколько подпоследовательностей.
 * Код Хэмминга 7-4 составляется по следующему принципу:
 * e1 e2 d1 e3 d2 d3 d4, где d1, d2, d3, d4 - элементы битовой последовательности
 * e1 = (d3 + d5 + d7) mod 2
 * e2 = (d3 + d6 + d7) mod 2
 * e3 = (d5 + d6 + d7) mod 2
 * Примечание: при необходимости добавить недостающие биты, незначащий нуль добавляется
 * в правую часть, т.к последовательность инвертирована.
 * \example 8(10) = 1011(2) => d3 = 1, d5 = 1, d6 = 0, d7 = 1
 * Найдем значения e: e1 = 1, e2 = 0, e3 = 0
 * Получим: 1010101
*/

class Encoder74  {
public:
    static EncodedBitSequence start(const BitSequence &data);

private:
    static void encode(const BitSequence &data, BitSequence &result);
};


#endif // ENCODER74_H
