#include "CyclicCodesLab.h"

CyclicCodesLab::CyclicCodesLab(CyclicLabView &view): labView(view) {
    bool arrOne[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bool arrTwo[] = {1, 1, 0, 1};
    SimplePolynomial polynomialOne(15, arrOne);
    SimplePolynomial polynomialTwo(3, arrTwo);

    Message message = CodeConverter::codeCRC(polynomialOne, polynomialTwo);

    message.switchBit(7);
    message.switchBit(5);
    message.switchBit(10);
    message.switchBit(9);

    SimplePolynomial check = CodeConverter::extractCRC(message, polynomialTwo);

    std::string label;
    if (CodeConverter::checkCorrectnessCRC(message, polynomialTwo)) {
        label = check.toString();
    } else {
        label = "Wrong";
    }

    view.setLabel(label);
}