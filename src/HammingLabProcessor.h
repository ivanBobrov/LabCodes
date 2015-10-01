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
    RUNNING,
    PAUSED
};

class HammingLabProcessor {
private:
    HammingLabProcessorState state;
    boost::thread* thread;
    boost::mutex mPauseMutex;
    boost::condition_variable mPausedChanged;
    HammingCodesLab* hammingCodesLab;

    Message* infoMessage;
    Message* codedMessage;

    HammingLabResult hammingLabResult;
    double probability;
    int attemptsCount;

    void execution();

public:
    HammingLabProcessor(HammingCodesLab* hammingCodesLab);
    ~HammingLabProcessor();

    bool start(const Message* info, double probability, int attemptsCount);
    bool pause();
    bool resume();

    HammingLabProcessorState getProcessorState();
};


#endif //HAMMING_CODES_HAMMING_LAB_RUNNABLE_H
