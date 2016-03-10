#ifndef CYCLIC_CODES_WIDGET_H
#define CYCLIC_CODES_WIDGET_H

#include <QtWidgets>
#include <string>
#include "CyclicLabView.h"
#include "CyclicCodesLab.h"

class CyclicCodesWidget : public QWidget, public CyclicLabView {

Q_OBJECT

private:

    QLabel *label;

public:
    CyclicCodesWidget(CyclicCodesLab &lab);

    void setLabel(std::string &label);
};

#endif