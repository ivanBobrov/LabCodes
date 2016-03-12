#include "CyclicCodesWidget.h"

CyclicCodesWidget::CyclicCodesWidget(ICyclicCodesLab &lab) : lab(&lab) {
    qRegisterMetaType<std::string>();

    eventHandler = new EventHandler(this);
    lab.setEventListener(eventHandler);

    QVBoxLayout *layout = new QVBoxLayout;
    this->label = new QLabel("asasas");
    this->button = new QPushButton("Нажми меня");
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(onButtonClick()));

    layout->addWidget(this->label);
    layout->addWidget(this->button);

    this->setLayout(layout);
}

CyclicCodesWidget::~CyclicCodesWidget() {
    delete eventHandler;
}

void CyclicCodesWidget::setLabel(std::string text) {
    QString string = QString::fromUtf8(text.c_str());
    label->setText(string);
}

void CyclicCodesWidget::onButtonClick() {
    std::vector<bool> vector;
    vector.push_back(true);
    vector.push_back(false);
    vector.push_back(true);
    vector.push_back(false);
    vector.push_back(false);
    vector.push_back(true);
    vector.push_back(true);

    std::vector<bool> gen;
    gen.push_back(true);
    gen.push_back(true);

    lab->buttonStartClicked(vector, gen, 20000, 0.0001);
}

void CyclicCodesWidget::onSendProcessFinished(CyclicLabResult result) {

}
