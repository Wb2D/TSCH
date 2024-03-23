#include "HammingCodeEngine/DataWorker\Converter\BigInteger\BigInteger.h"




/*!
 * \brief Метод возвращает строковое представление числа.
 * \param Отсутствуют.
 * \return Строковое представление числа.
*/
QString BigInteger::toString() const {
    QString result;
    for(int i = data.length() - 1; i >= 0; --i) {
        result += QString::number(data.at(i));
    }
    return result;
}


/*!
 * \brief Метод удаляет ведущие нули из числа.
 * \param Отсутствуют.
 * \return Отсутствуют.
*/
void BigInteger::removeZeros() {
    while(data.size() > 1 && data.last() == 0) {
        data.pop_back();
    }
}


/*!
 * \brief Метод выполняет деление числа на 2.
 * \param Отсутствуют.
 * \return Результат деления числа на 2.
*/
BigInteger BigInteger::div2() const {
    BigInteger result = *this;
    int carry = 0;
    for(int i = result.data.size() - 1; i >= 0; --i) {
        int current = result.data[i];
        int tmp = (carry * 10 + current) / 2;
        carry = current % 2;
        result.data[i] = tmp;
    }
    result.removeZeros();
    return result;
}


/*!
 * \brief Оператор сложения двух чисел.
 * \param number Второе число.
 * \return Результат сложения двух чисел.
*/
BigInteger BigInteger::operator+(const BigInteger &number) const {
    BigInteger result;
    int carry = 0;
    int maxSize = qMax(data.size(), number.data.size());
    for (int i = 0; i < maxSize; ++i) {
        int sum = carry;
        if (i < data.size()) {
            sum += data[i];
        }
        if (i < number.data.size()) {
            sum += number.data[i];
        }
        carry = sum / 10;
        sum = sum % 10;
        result.data.append(sum);
    }
    if (carry > 0) {
        result.data.append(carry);
    }
    return result;
}


/*!
 * \brief Оператор умножения числа на другое число.
 * \param number Второе число.
 * \return Результат умножения числа на другое число.
*/
BigInteger BigInteger::operator*(const BigInteger &number) const {
    BigInteger result("0");
    for (int i = 0; i < number.data.size(); ++i) {
        int carry = 0;
        BigInteger pResult;
        for (int j = 0; j < i; ++j) {
            pResult.data.append(0);
        }
        for (int j = 0; j < data.size(); ++j) {
            int prod = data[j] * number.data[i] + carry;
            pResult.data.append(prod % 10);
            carry = prod / 10;
        }
        if (carry > 0) {
            pResult.data.append(carry);
        }
        result = result + pResult;
    }
    return result;
}


/*!
 * \brief Метод проверяет, является ли число четным.
 * \param Отсутствуют.
 * \return true, если число четное, иначе false.
*/
bool BigInteger::isEven() const {
    return data.first() % 2;
}


/*!
 * \brief Метод проверяет, является ли число нулем.
 * \param Отсутствуют.
 * \return true, если число ноль, иначе false.
*/
bool BigInteger::isZero() const {
    return (data.size() == 1 && data[0] == 0);
}


/*!
 * \brief Метод добавляет цифру к числу.
 * \param digit Добавляемая цифра.
 * \return Отсутствуют.
*/
void BigInteger::append(const int &digit) {
    data.push_back(digit);
}


/*!
 * \brief Оператор доступа к цифре числа по индексу.
 * \param index Индекс цифры.
 * \return Цифра числа по указанному индексу.
*/
int BigInteger::operator[](const int& index) const {
    if (index < 0 || index > data.size()) {
        qWarning() << "ERROR : BitSequence -> bitsArray -> (index out of range)";
        return -1;
    }
    return data.at(index);
}


/*!
 * \brief Метод возвращает количество цифр в числе.
 * \param Отсутствуют.
 * \return Количество цифр в числе.
*/
int BigInteger::length() const {
    return data.size();
}


/*!
 * \brief Метод возвращает подчисло (подпоследовательность цифр) из числа.
 * \param from Начальный индекс.
 * \param to Конечный индекс.
 * \return Подчисло из числа.
*/
BigInteger BigInteger::subdigit(const int &from, const int &to) const {
    BigInteger result;
    for(int i = from; i <= to; ++i) {
        i >= this->length() ? result.append(0) : result.append(this->data.at(i));
    }
    return result;
}


/*!
 * \brief Метод заменяет значение в последовательности на случайное отличное от текущего.
 * \param index Индекс цифры.
 * \return Отсутствуют.
*/
void BigInteger::distort(const int &index) {
    data[index] = NumberGenerator::number(0, 9, data[index]);
}
