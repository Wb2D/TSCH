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


/*!
 * \brief Метод генерирует заданное чисто символов ASCII.
 * \details Я осознаю всю абсурдность поместить генератор ТЕКСТА в
 * класс - генератор чисел. Ну, что поделаешь. Не переименовывать же класс
 * и файлы из-за этого?
 * \param amount Число символов.
 * \return Случайно сгенерированный текст.
*/
QString NumberGenerator::generate(const int &amount) {
    QString result;
    QRandomGenerator rg = QRandomGenerator::securelySeeded();
    while(result.length() != amount) {
        result.push_back(static_cast<QChar>(rg.bounded(32, 126)));
    }
    return result;
}
