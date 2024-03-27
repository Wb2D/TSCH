#include "HammingCodeEngine/DataWorker/BigInteger/BigIntegerShell/bigIntegerShell.h"




/*!
 * \brief Конструктор создает пару значений из BigInteger, где заплнен только один элемент
 * \return Отсутствуют.
*/
BigIntegerShell::BigIntegerShell(const BigInteger &digit, const int &method, const int &size, const bool &flag) {
    this->method = method;
    this->size = size;
    int eSize = digit.length();
    if (eSize % size) {
        eSize += size - (eSize % size);
    }
    for(int i = 0; i < eSize; i += size) {
        BigInteger subDigit = digit.subdigit(i, i + size - 1);
        if(!flag) {
            this->data.push_back(QPair<BigInteger, BigInteger>(subDigit, BigInteger()));
        } else {
            this->data.push_back(QPair<BigInteger, BigInteger>(BigInteger(), subDigit));
        }
    }
}


/*!
 * \brief Оператор присваивания копирует данные из другого объекта BigIntegerShell.
 * \param obj Другой объект BigIntegerShell.
 * \return Ссылка на текущий объект BigIntegerShell.
*/
BigIntegerShell& BigIntegerShell::BigIntegerShell::operator=(const BigIntegerShell &obj) {
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
void BigIntegerShell::addError(const int &i, const int &j) {
    if(i < data.size() && j < size) {
        data[i].second.distort(j);
    } else {
        qDebug() << "ERROR : BigIntegerShell -> addError -> (index out of range)";
    }
}


/*!
 * \brief Метод возвращает строку, состоящую из парх первых значений.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
QString BigIntegerShell::getFirst() const {
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
QString BigIntegerShell::getSecond() const {
    QString result;
    for(const auto &i : data) {
        result.push_front(i.second.toString());
    }
    return result;
}
