#ifndef HAMMING_CODES_HAMMING_LAB_RUNNABLE_H
#define HAMMING_CODES_HAMMING_LAB_RUNNABLE_H

#include <boost/thread/thread.hpp>
#include "Message.h"
#include "HammingCodesLab.h"
#include "HammingLabResult.h"
#include "EnvironmentImitator.h"

class HammingCodesLab;

enum class HammingLabProcessorState {
    READY,
    RUNNING
};

class HammingLabProcessor {
private:
    HammingLabProcessorState state;
    boost::thread* thread;
    HammingCodesLab* hammingCodesLab;

    Message* infoMessage;
    Message* codedMessage;

    HammingLabResult hammingLabResult;
    double probability;
    int attemptsCount;
    int currentAttempt;

    void execution();

public:
    HammingLabProcessor(HammingCodesLab* hammingCodesLab);
    ~HammingLabProcessor();

    bool start(const Message* info, double probability, int attemptsCount);

    HammingLabProcessorState getProcessorState();
};


#endif //HAMMING_CODES_HAMMING_LAB_RUNNABLE_H
