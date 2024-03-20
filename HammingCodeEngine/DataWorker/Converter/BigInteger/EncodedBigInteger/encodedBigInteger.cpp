#include "HammingCodeEngine/DataWorker/Converter/BigInteger/EncodedBigInteger/encodedBigInteger.h"




/*!
 * \brief Метод возвращает строковое представление закодированного числа.
 * \param Отсутствуют.
 * \return Строковое представление закодированного числа.
*/
const QString EncodedBigInteger::toString() const {
    return QString("Encoded sequency: " + digit.toString() + ", Method: " +
                   method + ", Time: " + QString::number(time) + ", Splitting:"
                   + QString::number(iteration));
}
