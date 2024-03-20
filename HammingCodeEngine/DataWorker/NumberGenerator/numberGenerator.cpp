#include "HammingCodeEngine\DataWorker\NumberGenerator\numberGenerator.h"




const QString NumberGenerator::arr = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


/*!
 * \brief Метод генерирует случайную строку чисел с заданным основанием и длиной.
 * \param base Основание системы счисления.
 * \param digits Число разрядов.
 * \return Случайно сгенерированное число в формате строки.
*/
QString NumberGenerator::generate(const int &base, const int &digits) {
    if (base < 0 || base > 36) {
        qDebug() << "ERROR : NumberGenerator -> generate -> wrong base";
    }
    QRandomGenerator rg = QRandomGenerator::securelySeeded();
    QString result;
    for (int i = 0; i < digits; ++i) {
        int index = (i == 0) ? rg.bounded(1, base) : rg.bounded(base);
        result.append(arr.at(index));
    }
    return result;
}
