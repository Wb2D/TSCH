#ifndef _numberGenerator_h
#define _numberGenerator_h

/// данный класс является частью HammindCodeEngine, что будет полноценно внедрен позже

#include <QString>
#include <QDebug>
#include <QRandomGenerator>

class NumberGenerator {
public:
    // метод для генерации случайного числа
    static QString generate(const int &base, const int &digits);
private:
    // строка возможных символов
    static const QString arr;
};

#endif
