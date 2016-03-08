#include "CyclicCodesLab.h"

CyclicCodesLab::CyclicCodesLab(CyclicLabView &view): labView(view) {
    bool arrOne[] = {0, 0, 1, 1, 1, 0, 0, 0, 0, 1};
    bool arrTwo[] = {0, 0, 1, 0, 1};
    SimplePolynomial polynomialOne(9, arrOne);
    SimplePolynomial polynomialTwo(4, arrTwo);
    SimplePolynomial remainder;
    polynomialOne.division(polynomialTwo, remainder);

    Message message = CodeConverter::polynomialToMessage(polynomialOne);
    SimplePolynomial poly = CodeConverter::messageToPolynomial(message);

    std::string label = poly.toString();
    view.setLabel(label);
}