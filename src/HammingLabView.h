#ifndef HAMMING_CODES_HAMMING_LAB_VIEW_H
#define HAMMING_CODES_HAMMING_LAB_VIEW_H

#include "HammingLabResult.h"

class HammingLabView {
public:
    virtual void onStartProcess() = 0;
    virtual void onPauseProcess() = 0;
    virtual void onResumeProcess() = 0;

    virtual void onInformationMessageChanged(std::vector<bool> &infoMessage, std::vector<bool> &codedMessage) = 0;
    virtual void onProbabilityChanged(double newProbability) = 0;
    virtual void onAttemptsCountChanged(int newAttemptsCount) = 0;

    virtual void onResultsChanged(HammingLabResult &results) = 0;
    virtual void onSendProcessFinished(HammingLabResult &results) = 0;
};

#endif //HAMMING_CODES_HAMMING_LAB_VIEW_H
