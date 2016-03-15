#include "CyclicPolynomialLabel.h"


CyclicPolynomialLabel::CyclicPolynomialLabel() {
    setTextFormat(Qt::RichText);
}

void CyclicPolynomialLabel::setPolynomial(std::vector<bool> &polynomial, int controlBitsCount) {
    QString text;

    std::vector<bool>::iterator iterator = polynomial.end() - 1;
    QString infoText;
    for (iterator; iterator >= polynomial.begin() + controlBitsCount; --iterator) {
        QString plain = *iterator ? "1" : "0";
        infoText.append(plain);
    }

    QString controlText;
    for (iterator; iterator >= polynomial.begin(); --iterator) {
        QString plain = *iterator ? "1" : "0";
        controlText.append(plain);
    }

    text.append(getNormalText(infoText));
    text.append(getControlText(controlText));

    setText(text);
}

QString CyclicPolynomialLabel::getNormalText(QString &text) {
    return "<span style='color: #335577; font-size: 20px;'>" + text + "</span>";
}

QString CyclicPolynomialLabel::getControlText(QString &text) {
    return "<span style='color: #aa5533; font-size: 20px;'>" + text + "</span>";
}
