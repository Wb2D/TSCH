#ifndef ENCODER1511_H
#define ENCODER1511_H

#include <QElapsedTimer>
#include <QPair>

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"
#include "HammingCodeEngine/DataWorker/BitSequence/BitSequenceShell/bitSequenceShell.h"




/*!
 * \brief Класс Encoder1511 реализует алгоритм перевода последовательности бит в код Хэмминга 15-11.
 * \author Wb2D
 * \date 2 октября 2023
 * \details Данный класс разбивает битовую последовательность на части и кодирует каждую часть
 * по алгоритму кода Хэмминга 15-11. В случае, если размерность превышает 11, последовательность 
 * будет разбита на несколько подпоследовательностей.
 * Код Хэмминга 15-11 составляется по следующему принципу:
 * e1 e2 d1 e3 d2 d3 d4 e4 d5 d6 d7 d8 d9 d10 d11  - элементы битовой последовательности
 * e1 = (d1 + d2 + d4 + d5 + d7 + d9 + d11) mod2
 * e2 = (d1 + d3 + d4 + d6 + d7 + d10 + d11) mod2
 * e3 = (d2 + d3 + d4 + d8 + d9 + d10 + d11) mod2
 * e4 = (d5 + d6 + d7 + d8 + d9 + d10 + d11) mod2
 * Примечание: при необходимости добавить недостающие биты, незначащий нуль добавляется
 * в правую часть, т.к последовательность инвертирована.
*/

class Encoder1511 {
public:
    static BitSequenceShell start(const BitSequence &data);

private:
    static void encode(const BitSequence &data, BitSequence &result);
};


#endif // ENCODER1511_H
