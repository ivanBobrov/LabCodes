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

    static const int UPDATE_TIMER_DELAY_MILLIS = 100;

    ICyclicCodesLab *lab;
    EventHandler *eventHandler;

    QTimer *updateTimer;

    QPushButton *startButton;
    QLabel *receivedCorrectlyResult;
    QLabel *experimentsDoneResult;
    QLabel *errorDetectedResult;
    QLabel *errorMissedResult;
    QProgressBar *progressBar;

    void createLayouts();
    QLayout* createInputLayout();
    QLayout* createCommandLayout();
    QLayout* createOutputLayout();
    QLayout* createProgressBarLayout();

public:
    CyclicCodesWidget(ICyclicCodesLab &lab);
    ~CyclicCodesWidget();

public slots:
    void onButtonClick();
    void onSendProcessFinished(CyclicLabResult result);
    void updateResult();
    void setInfo(std::string label);

};

#endif