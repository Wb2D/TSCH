#ifndef ENCODEDBITSEQUENCE_H
#define ENCODEDBITSEQUENCE_H

#include <QDateTime>
#include <QVector>
#include <QPair>
#include <QString>

#include "HammingCodeEngine/DataWorker/BitSequence/bitSequence.h"




/*!
 * \brief Класс EncodedBitSequence является оберткой для объекта BitSequence.
 * \author Wb2D
 * \date 22 сентября 2023
 * \details Он добавляет к исходному классу информацию о примененном методе кодирования,
 *  количестве частей, на которые была разбита исходная последовательность, и времени, 
 * затраченном на кодирование.
*/

class EncodedBitSequence {
public:
    EncodedBitSequence() : data(), method(0), time(0), iteration(0) {}
    EncodedBitSequence(const QVector<QPair<BitSequence, BitSequence>> &data, const int &method,
                       const qint64 &time, const int &iteration) : data(data), method(method), time(time),
                       iteration(iteration) {   }
    EncodedBitSequence(const EncodedBitSequence &obj)
        : data(obj.data), method(obj.method), time(obj.time), iteration(obj.iteration) {    }
    EncodedBitSequence& operator=(const EncodedBitSequence&);
    QPair<BitSequence, BitSequence>& operator[](int index) { return data[index]; }
    const QPair<BitSequence, BitSequence>& operator[](int index) const { return data[index]; }
    void setData(const QVector<QPair<BitSequence, BitSequence>> &data) { this->data = data; }
    const QVector<QPair<BitSequence, BitSequence>> &getData() const { return data; }
    void addData(const QPair<BitSequence, BitSequence> &pair) { data.push_back(pair); }
    void setMethod(const int &method) { this->method = method; }
    const int &getMethod() const { return method; }
    void setTime(const qint64 &time) { this->time = time; }
    const qint64 &getTime() const { return time; }
    void setIteration(const int &iteration) { this->iteration = iteration; }
    const int &getIteration() const { return iteration; }
    void set(const QVector<QPair<BitSequence, BitSequence>>&, const int&, const qint64&, const int&);

private:
    QVector<QPair<BitSequence, BitSequence>> data; ///< пара из обычной и закодированной посл.
    int method; ///< алгоритм, используемый для кодирование
    qint64 time; ///< время, затраченное на кодирование
    int iteration; ///< число частей, на которые была разбита последовательность при кодировании
};


#endif // ENCODEDBITSEQUENCE_H
