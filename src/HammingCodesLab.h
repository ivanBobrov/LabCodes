#ifndef HAMMING_CODES_HAMMING_CODES_LAB_H
#define HAMMING_CODES_HAMMING_CODES_LAB_H

#include <vector>
#include <boost/thread/thread.hpp>
#include "CodeConverter.h"
#include "Message.h"
#include "HammingLabView.h"
#include "HammingLabProcessor.h"
#include "HammingLabResult.h"

class HammingLabProcessor;

class HammingCodesLab {
private:
    static std::vector<bool> DEFAULT_INFORMATION_MESSAGE;
    static const double DEFAULT_PROBABILITY;
    static const int DEFAULT_ATTEMPTS_COUNT;

    int attemptsCount;
    double corruptionProbability;
    Message *information;
    Message *codedMessage;

    HammingLabView *hammingLabView;
    HammingLabProcessor *hammingLabProcessor;

    HammingCodesLab(HammingLabView *hammingLabView);

public:
    ~HammingCodesLab();
    static HammingCodesLab* createInstance(HammingLabView *hammingLabView);

    void startSendProcess();
    void pauseSendProcess();

    void setInformationMessage(std::vector<bool> &infoMessage);
    void setProbability(double probability);
    void setAttemptsCount(int count);

    void updateResults(HammingLabResult &result);
    void sendProcessFinished(HammingLabResult &results);

};


#endif //HAMMING_CODES_HAMMING_CODES_LAB_H
