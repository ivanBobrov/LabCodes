#include "CyclicCodesWidget.h"

CyclicCodesWidget::CyclicCodesWidget(ICyclicCodesLab &lab) {
    this->lab = &lab;

    QVBoxLayout *layout = new QVBoxLayout;
    this->label = new QLabel("asasas");
    this->button = new QPushButton("Нажми меня");
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(onButtonClick()));

    layout->addWidget(this->label);
    layout->addWidget(this->button);

    this->setLayout(layout);
}

void CyclicCodesWidget::setLabel(std::string &text) {
    QString string = QString::fromUtf8(text.c_str());
    label->setText(string);
}

void CyclicCodesWidget::onButtonClick() {
    lab->buttonStartClicked();
}
