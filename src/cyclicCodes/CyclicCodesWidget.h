#ifndef CYCLIC_CODES_WIDGET_H
#define CYCLIC_CODES_WIDGET_H

#include <QtWidgets>
#include <string>

#include "CyclicLabView.h"

class CyclicCodesWidget : public QWidget, public CyclicLabView {

Q_OBJECT

private:

    QLabel *label;

public:
    CyclicCodesWidget();

    void setLabel(std::string &label);
};

#endif