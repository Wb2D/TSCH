#ifndef ENCODERDECIMAL1511_H
#define ENCODERDECIMAL1511_H

#include "HammingCodeEngine/DataWorker/Converter/BigInteger/BigInteger.h"
#include "HammingCodeEngine/DataWorker/Converter/BigInteger/EncodedBigInteger/encodedBigInteger.h"




/*!
 * \brief Класс EncoderDecimal1511 реализует алгоритм перевода последовательности бит в код 
 * Хэмминга 15-11.
 * \author Wb2D
 * \date 2 октября 2023
 * \details Данный класс разбивает битовую последовательность на части и кодирует каждую часть
 * по алгоритму кода Хэмминга 15-11. В случае, если размерность превышает 11, последовательность 
 * будет разбита на несколько подпоследовательностей.
 * Код Хэмминга 15-11 для десятичных чисел составляется по следующему принципу:
 * e1 e2 d1 e3 d2 d3 d4 e4 d5 d6 d7 d8 d9 d10 d11  - элементы битовой последовательности
 * e1 = (d1 + d2 + d4 + d5 + d7 + d9 + d11) mod10
 * e2 = (d1 + d3 + d4 + d6 + d7 + d10 + d11) mod10
 * e3 = (d2 + d3 + d4 + d8 + d9 + d10 + d11) mod10
 * e4 = (d5 + d6 + d7 + d8 + d9 + d10 + d11) mod10
 * Примечание: при необходимости добавить недостающие биты, незначащий нуль добавляется
 * в правую часть, т.к последовательность инвертирована.
*/

class EncoderDecimal1511 {
public:
    static EncodedBigInteger start(const BigInteger &data);

private:
    static void encode(const BigInteger &data, BigInteger &result);
};


#endif // ENCODERDECIMAL1511_H
