#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <QString>
#include <QDebug>
#include <QRandomGenerator>




/*!
 * \brief Класс NumberGenerator предназначен для генерации случайных чисел
 * с указанным числом разрядов и в заданной системе счисления.
 * \author Wb2D.
 * \date 23 сентября 2023
 * \details Этот класс предоставляет метод для генерации случайного числа
 * в указанной системе счисления с заданным числом разрядов.
*/

class NumberGenerator {
public:
    static QString generate(const int&, const int&);
    static QString generate(const int&);
    static int number(const int&, const int&);
    static int number(const int&, const int&, const int&);

private:
    static const QString arr; //!< Строка с символами для генерации чисел.
};


#endif // NUMBERGENERATOR_H
