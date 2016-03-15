#ifndef HAMMING_CODES_CYCLIC_POLYNOMIAL_LABEL_H
#define HAMMING_CODES_CYCLIC_POLYNOMIAL_LABEL_H


#include <QtWidgets/qlabel.h>

class CyclicPolynomialLabel : public QLabel {

Q_OBJECT

private:
    QString getNormalText(QString &text);
    QString getControlText(QString &text);

public:
    CyclicPolynomialLabel();

    void setPolynomial(std::vector<bool> &polynomial, int controlBitsCount);

};


#endif //HAMMING_CODES_CYCLIC_POLYNOMIAL_LABEL_H
