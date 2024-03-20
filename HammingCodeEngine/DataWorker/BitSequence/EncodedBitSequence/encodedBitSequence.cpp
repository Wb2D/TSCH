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
        time = obj.time;
        iteration = obj.iteration;
    }
    return *this;
}


/*!
 * \brief Метод задает новые значения объекту класса.
 * \param data Закодированная битовая последовательность.
 * \param method Метод кодирования.
 * \param time Время кодирования.
 * \param iteration Количество итераций разбиения.
 * \return Отсутствуют.
 */
void EncodedBitSequence::set(const QVector<QPair<BitSequence, BitSequence>> &data,
                             const int &method, const qint64 &time, const int &iteration) {
    this->setData(data);
    this->setMethod(method);
    this->setTime(time);
    this->setIteration(iteration);
}
