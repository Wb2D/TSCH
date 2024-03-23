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
        size = obj.size;
    }
    return *this;
}


/*!
 * \brief Оператор изменяет указанную цифру в последовательности.
 * \param i Индекс последовательности.
 * \return Отсутствуют.
*/
void EncodedBigInteger::addError(const int &i, const int &j) {
    if(i < data.size() && j < size) {
        data[i].second.distort(j);
    } else {
        qDebug() << "ERROR : EncodedBitSequence -> addError -> (index out of range)";
    }
}
