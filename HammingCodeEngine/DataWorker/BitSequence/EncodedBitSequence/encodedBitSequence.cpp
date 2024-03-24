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
        size = obj.size;
    }
    return *this;
}


/*!
 * \brief Оператор изменяет указанный бит в последовательности.
 * \param i Индекс последовательности.
 * \return Отсутствуют.
*/
void EncodedBitSequence::addError(const int &i, const int &j) {
    if(i < data.size() && j < size) {
        data[i].second.reverse(j);
    } else {
        qDebug() << "ERROR : EncodedBitSequence -> addError -> (index out of range)";
    }
}


/*!
 * \brief Оператор возвращает строку, состоящую из парх первых значений.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
QString EncodedBitSequence::getFirst() const {
    QString result;
    for(const auto &i : data) {
        result.push_front(i.first.toString());
    }
    return result;
}


/*!
 * \brief Оператор возвращает строку, состоящую из парх вторых значений.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
QString EncodedBitSequence::getSecond() const {
    QString result;
    for(const auto &i : data) {
        result.push_front(i.second.toString());
    }
    return result;
}
