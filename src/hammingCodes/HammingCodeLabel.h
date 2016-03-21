#ifndef HAMMING_CODES_HAMMING_CODE_LABEL_H
#define HAMMING_CODES_HAMMING_CODE_LABEL_H

#include <QtWidgets/qlabel.h>

class HammingCodeLabel : public QLabel {

Q_OBJECT

private:
    QString getNormalText(QString &text);
    QString getControlText(QString &text);

public:
    HammingCodeLabel();
    void setMessage(std::vector<bool> &message);
};


#endif //HAMMING_CODES_HAMMING_CODE_LABEL_H
