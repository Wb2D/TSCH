#include "HammingCodeEngine/DataWorker\BitSequence\bitSequence.h"




/*!
 * \brief Метод изменяет размер последовательности битов.
 * \param length Новая длина последовательности.
 * \return Отсутствуют.
*/
void BitSequence::resize(const int& length) {
    int newLength = (length == 0) ? 1 : (length * 2);
    bool* newArray = new bool[newLength];
    if (bitArray) {
        for (int i = 0; i < bitCount; ++i) {
            *(newArray + i) = *(bitArray + i);
        }
    }
    delete[] bitArray;
    bitArray = newArray;
    arraySize = newLength;
}


/*!
 * \brief Оператор доступа к биту по индексу.
 * \param index Индекс бита.
 * \return Значение бита по указанному индексу.
*/
bool BitSequence::operator[](const int& index) const {
    if (index < 0 || index >= bitCount) {
        qWarning() << "ERROR : BitSequence -> bitsArray -> (index out of range)";
        return false;
    }
    return *(bitArray + index);
}


/*!
 * \brief Метод устанавливает значение бита по указанному индексу.
 * \param index Индекс бита.
 * \param value Новое значение бита.
 * \return Отсутствуют.
*/
void BitSequence::set(const int& index, const bool& value) {
    if (index < 0 || index >= bitCount) {
        qWarning() << "ERROR : BitSequence -> bitsArray -> (index out of range)";
        return;
    }
    *(bitArray + index) = value;
}


/*!
 * \brief Метод добавляет новый бит в конец последовательности.
 * \param value Значение добавляемого бита.
 * \return Отсутствуют.
*/
void BitSequence::append(const bool& value) {
    ++bitCount;
    if(bitCount > arraySize) {
        resize(arraySize);
    }
    set(bitCount - 1, value);
}


/*!
 * \brief Метод возвращает строковое представление последовательности битов.
 * \param Отсутствуют.
 * \return Строковое представление последовательности битов.
*/
QString BitSequence::toString() const {
    QString result;
    for (int i = bitCount - 1; i >= 0; --i) {
        result.append(bitArray[i] ? '1' : '0');
    }
    return result;
}


/*!
 * \brief Метод возвращает подпоследовательность битов в заданном диапазоне.
 * \param from Начальный индекс подпоследовательности.
 * \param to Конечный индекс подпоследовательности.
 * \return Подпоследовательность битов в заданном диапазоне.
*/
BitSequence BitSequence::subsequence(int from, int to) const {
    BitSequence result;
    for(int i = from; i <= to; ++i) {
        i >= length() ? result.append(false) : result.append(*(bitArray + i));
    }
    return result;
}
