#ifndef CYCLIC_CODES_WIDGET_H
#define CYCLIC_CODES_WIDGET_H

#include <QtWidgets>
#include <string>
#include "CyclicLabView.h"
#include "CyclicCodesLab.h"

class CyclicCodesWidget : public QWidget, public CyclicLabView {

Q_OBJECT

private:
    ICyclicCodesLab *lab;

    QLabel *label;
    QPushButton *button;

public:
    CyclicCodesWidget(ICyclicCodesLab &lab);

    void setLabel(std::string &label);

public slots:
    void onButtonClick();

};

#endif