#include "HammingCodeEngine/DataWorker/BitSequence/BitSequenceShell/bitSequenceShell.h"




/*!
 * \brief Конструктор BitSequenceShell, создающий оболочку для битовой последовательности.
 * \param seq Исходная битовая последовательность.
 * \param method Метод кодирования.
 * \param size Размер подпоследовательности.
 * \param flag Флаг, указывающий на тип данных в оболочке (true - вторая половина, false - первая половина).
 * \return Отсутствуют.
*/
BitSequenceShell::BitSequenceShell(const BitSequence &seq, const int &method, const int &size, const bool &flag) {
    this->method = method;
    this->size = size;
    int eSize = seq.length();
    if (eSize % size) {
        eSize += size - (eSize % size);
    }
    for(int i = 0; i < eSize; i += size) {
        BitSequence subseq = seq.subsequence(i, i + size - 1);
        if(!flag) {
            this->data.push_back(QPair<BitSequence, BitSequence>(subseq, BitSequence()));
        } else {
            this->data.push_back(QPair<BitSequence, BitSequence>(BitSequence(), subseq));
        }
    }
}


/*!
 * \brief Оператор присваивания копирует данные из другого объекта BitSequenceShell.
 * \param obj Другой объект BitSequenceShell.
 * \return Ссылка на текущий объект BitSequenceShell.
*/
BitSequenceShell& BitSequenceShell::operator=(const BitSequenceShell &obj) {
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
void BitSequenceShell::addError(const int &i, const int &j) {
    if(i < data.size() && j < size) {
        data[i].second.reverse(j);
    } else {
        qDebug() << "ERROR : BitSequenceShell -> addError -> (index out of range)";
    }
}


/*!
 * \brief Метод возвращает строку, состоящую из парх первых значений.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
QString BitSequenceShell::getFirst() const {
    QString result;
    for(const auto &i : data) {
        result.push_front(i.first.toString());
    }
    return result;
}


/*!
 * \brief Метод возвращает строку, состоящую из парх вторых значений.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
QString BitSequenceShell::getSecond() const {
    QString result;
    for(const auto &i : data) {
        result.push_front(i.second.toString());
    }
    return result;
}
