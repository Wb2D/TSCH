#include "HammingCodeEngine/DataWorker/Converter/BigInteger/EncodedBigInteger/encodedBigInteger.h"




/*!
 * \brief Оператор присваивания копирует данные из другого объекта EncodedBigInteger.
 * \param obj Другой объект EncodedBigInteger.
 * \return Ссылка на текущий объект EncodedBigInteger.
*/
EncodedBigInteger& EncodedBigInteger::EncodedBigInteger::operator=(const EncodedBigInteger &obj) {
    if(this != &obj) {
        data =  obj.data;
        method = obj.method;
        iteration = obj.iteration;
    }
    return *this;
}
