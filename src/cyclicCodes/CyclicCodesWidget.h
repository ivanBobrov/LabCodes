#ifndef CYCLIC_CODES_WIDGET_H
#define CYCLIC_CODES_WIDGET_H

#include <QtWidgets>
#include <string>
#include "CyclicCodesLab.h"

Q_DECLARE_METATYPE (std::string)
Q_DECLARE_METATYPE (CyclicLabResult)

class CyclicCodesWidget : public QWidget {

Q_OBJECT

private:

    class EventHandler : public ICyclicCodesLab::EventListener {
    private:
        CyclicCodesWidget *mInstance;
    public:
        EventHandler(CyclicCodesWidget *pInstance) : mInstance(pInstance) {}

        virtual void onSendProcessFinished(CyclicLabResult result) {
            QMetaObject::invokeMethod(mInstance, "onSendProcessFinished", Q_ARG(CyclicLabResult, result));
        }

        virtual void setInfo(std::string label) {
            QMetaObject::invokeMethod(mInstance, "setInfo", Q_ARG(std::string, label));
        }
    };

    ICyclicCodesLab *lab;
    EventHandler *eventHandler;

    QLabel *label;
    QPushButton *button;

public:
    CyclicCodesWidget(ICyclicCodesLab &lab);
    ~CyclicCodesWidget();

public slots:
    void onButtonClick();
    void onSendProcessFinished(CyclicLabResult result);
    void setInfo(std::string label);

};

#endif