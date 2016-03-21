#include "HammingCodeLabel.h"

HammingCodeLabel::HammingCodeLabel() {
    setTextFormat(Qt::RichText);
}

QString HammingCodeLabel::getNormalText(QString &text) {
    return "<span style='color: #335577; font-size: 18px;'>" + text + "</span>";
}

QString HammingCodeLabel::getControlText(QString &text) {
    return "<span style='color: #aa5533; font-size: 18px;'>" + text + "</span>";
}

void HammingCodeLabel::setMessage(std::vector<bool> &message) {
    QString result = "";

    int curr = 1;
    int next = 2;
    for (std::vector<bool>::iterator it = message.begin(); it < message.end(); it++) {
        QString value = *it ? "1" : "0";
        QString richString;

        if (curr * 2 == next) {
            next *= 2;
            richString = getControlText(value);
        } else {
            richString = getNormalText(value);
        }

        ++curr;
        //result.append(richString);
        result.insert(0, richString);
    }

    setText(result);
}
