#ifndef HAMMING_CODES_TASK_RUNNER_H
#define HAMMING_CODES_TASK_RUNNER_H

#include <boost/thread/thread.hpp>
#include <vector>
#include "CyclicLabResult.h"

class LabTask {
public:
    virtual void task() = 0;

    bool isFinished();

    void run();

    class OnCompleteListener {
    public:
        virtual void onTaskComplete() = 0;
    };

    void setOnCompleteListener(OnCompleteListener *listener);

private:
    bool finished = false;
    boost::mutex finishedMutex;
    OnCompleteListener *completeListener = nullptr;
};

class LabTaskRunner {

private:
    std::vector<boost::thread *> *threadList = new std::vector<boost::thread *>();

public:

    LabTaskRunner();
    ~LabTaskRunner();

    void submitTask(LabTask& task);
    void interruptAllThreads();
    void removeFinishedThread();
    void joinAllThreads();
};

#include "CyclicLabTask.h"
#endif //HAMMING_CODES_TASK_RUNNER_H
