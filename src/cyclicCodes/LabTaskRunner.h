#ifndef HAMMING_CODES_TASK_RUNNER_H
#define HAMMING_CODES_TASK_RUNNER_H

#include <boost/thread/thread.hpp>
#include <vector>
#include "CyclicLabResult.h"

class LabTask {
private:
    bool finished = false;
    boost::mutex finishedMutex;

public:
    virtual void task() = 0;

    bool isFinished() {
        boost::lock_guard<boost::mutex> lock(finishedMutex);
        return finished;
    }

    void run();
};

class LabTaskRunner {

private:
    std::vector<boost::thread *> *threadList = new std::vector<boost::thread *>();

public:

    LabTaskRunner();
    ~LabTaskRunner();

    void submitTask(LabTask& task);
    void removeFinishedThread();
    void joinAllThreads();
};

#include "CyclicLabTask.h"
#endif //HAMMING_CODES_TASK_RUNNER_H
