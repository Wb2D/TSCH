#include "HammingCodeEngine/DataWorker/BitSequence/EncodedBitSequence/encodedBitSequence.h"




/*!
 * \brief Оператор присваивания копирует данные из другого объекта EncodedBitSequence.
 * \param obj Другой объект EncodedBitSequence.
 * \return Ссылка на текущий объект EncodedBitSequence.
*/
EncodedBitSequence& EncodedBitSequence::operator=(const EncodedBitSequence &obj) {
    if (this != &obj) {
        data = obj.data;
        method = obj.method;
        iteration = obj.iteration;
    }
    return *this;
}
