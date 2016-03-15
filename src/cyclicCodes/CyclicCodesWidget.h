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

        virtual void onBreakProcess(CyclicLabResult lastObtainedResult) {
            QMetaObject::invokeMethod(mInstance, "onSendProcessBreak", Q_ARG(CyclicLabResult, lastObtainedResult));
        };
    };

    static const int UPDATE_TIMER_DELAY_MILLIS = 50;

    ICyclicCodesLab *lab;
    EventHandler *eventHandler;

    QTimer *updateTimer;

    QPushButton *startButton;
    QPushButton *stopButton;
    QLabel *receivedCorrectlyResult;
    QLabel *experimentsDoneResult;
    QLabel *errorDetectedResult;
    QLabel *errorMissedResult;
    QLineEdit *informationPolyEdit;
    QComboBox *generatorListChooser;
    QLineEdit *experimentsCountEdit;
    QLineEdit *probabilityEdit;
    QProgressBar *progressBar;

    void createLayouts();
    QGroupBox * createInputLayout();
    QGroupBox * createCommandLayout();
    QGroupBox * createOutputLayout();

    void parseBoolVector(std::vector<bool> &output, const QString &text);
    void showResults(CyclicLabResult &result);

public:
    CyclicCodesWidget(ICyclicCodesLab &lab);
    ~CyclicCodesWidget();

public slots:
    void onButtonStartClick();
    void onButtonStopClick();
    void onSendProcessFinished(CyclicLabResult result);
    void onSendProcessBreak(CyclicLabResult result);
    void updateResult();
    void setInfo(std::string label);

};

#endif