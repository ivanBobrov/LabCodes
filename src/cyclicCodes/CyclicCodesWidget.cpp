#include "CyclicCodesWidget.h"

CyclicCodesWidget::CyclicCodesWidget() {
    QVBoxLayout layout;
    //QLabel *label = new QLabel("Hello, world!", this);
    this->label = new QLabel("asasa", this);
    layout.addWidget(this->label);

    this->setLayout(&layout);
}

void CyclicCodesWidget::setLabel(std::string &text) {
    QString string = QString::fromUtf8(text.c_str());
    label->setText(string);
}