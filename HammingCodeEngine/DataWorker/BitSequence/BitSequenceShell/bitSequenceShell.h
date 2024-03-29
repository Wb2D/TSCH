#ifndef BitSequenceShell_H
#define BitSequenceShell_H

#include <QDateTime>
#include <QVector>
#include <QPair>
#include <QString>

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"




/*!
 * \brief Класс BitSequenceShell является оберткой для объекта BitSequence.
 * \author Wb2D
 * \date 22 сентября 2023
 * \details Он добавляет к исходному классу информацию о примененном методе кодирования,
 *  количестве частей, на которые была разбита исходная последовательность, и времени, 
 * затраченном на кодирование.
*/

class BitSequenceShell {
public:
    BitSequenceShell() : data(), method(0), size(0) {    }
    BitSequenceShell(const BitSequence&, const int&, const int&, const bool&);
    BitSequenceShell(const QVector<QPair<BitSequence, BitSequence>> &data, const int &method,
                       const int &size) : data(data), method(method), size(size) {   }
    BitSequenceShell(const BitSequenceShell &obj)
        : data(obj.data), method(obj.method),  size(obj.size) {    }
    BitSequenceShell& operator=(const BitSequenceShell&);
    QPair<BitSequence, BitSequence>& operator[](int index) { return data[index]; }
    const QPair<BitSequence, BitSequence>& operator[](int index) const { return data[index]; }
    void setData(const QVector<QPair<BitSequence, BitSequence>> &data) { this->data = data; }
    const QVector<QPair<BitSequence, BitSequence>> &getData() const { return data; }
    void addData(const QPair<BitSequence, BitSequence> &pair) { data.push_back(pair); }
    void setMethod(const int &method) { this->method = method; }
    const int &getMethod() const { return method; }
    void setSize(const int &size) { this->size = size; }
    const int &getSize() const { return size; }
    int getAmount() const { return data.length(); }
    void addError(const int&, const int&);

    QString getFirst() const;
    QString getSecond() const;

private:
    QVector<QPair<BitSequence, BitSequence>> data; ///< пара из обычной и закодированной посл.
    int method; ///< алгоритм, используемый для кодирование
    int size; ///< размер последовательности
};


#endif // BitSequenceShell_H
