#ifndef HAMMING_CODES_HAMMING_LAB_EVENT_EMITTER_H
#define HAMMING_CODES_HAMMING_LAB_EVENT_EMITTER_H

#include <QtWidgets>
#include "HammingLabView.h"

class HammingLabEventEmitter : public QObject, public HammingLabView {

Q_OBJECT

private:

public:

    HammingLabEventEmitter();

    virtual void onStartProcess() override;
    virtual void onPauseProcess() override;
    virtual void onResumeProcess() override;
    virtual void onInformationMessageChanged(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage) override;
    virtual void onProbabilityChanged(double newProbability) override;
    virtual void onAttemptsCountChanged(int newAttemptsCount) override;
    virtual void onResultsChanged(HammingLabResult &results) override;
    virtual void onSendProcessFinished(HammingLabResult &results) override;

signals:
    void startProcessSignal();
    void pauseProcessSignal();
    void resumeProcessSignal();
    void informationMessageChangedSignal(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage);
    void probabilityChangedSignal(double newProbability);
    void attemptsCountChangedSignal(int newAttemptsCount);
    void resultsChangedSignal(const HammingLabResult &results);
    void sendProcessFinishedSignal(const HammingLabResult &results);
};


#endif //HAMMING_CODES_HAMMING_LAB_EVENT_EMITTER_H