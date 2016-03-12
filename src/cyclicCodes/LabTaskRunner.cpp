#include "LabTaskRunner.h"

void LabTask::run() {
    task();
    finishedMutex.lock();
    finished = true;
    finishedMutex.unlock();

    if (completeListener != nullptr) {
        completeListener->onTaskComplete();
    }
}

bool LabTask::isFinished() {
    boost::lock_guard<boost::mutex> lock(finishedMutex);
    return finished;
}

void LabTask::setOnCompleteListener(OnCompleteListener *listener) {
    this->completeListener = listener;
}

LabTaskRunner::LabTaskRunner() {

}

LabTaskRunner::~LabTaskRunner() {
    delete threadList;
}

void LabTaskRunner::submitTask(LabTask &task) {
    boost::thread *worker = new boost::thread(boost::bind(&LabTask::run, &task));
    threadList->push_back(worker);
}

void LabTaskRunner::removeFinishedThread() {
    for (std::vector<boost::thread *>::iterator it = threadList->begin(); it < threadList->end(); ) {
        boost::thread *worker = *it;
        if (worker->timed_join(boost::posix_time::seconds(0))) {
            delete worker;
            it = threadList->erase(it);
        } else {
            ++it;
        }
    }
}

void LabTaskRunner::joinAllThreads() {
    for (std::vector<boost::thread *>::iterator it = threadList->begin(); it < threadList->end(); ++it) {
        boost::thread *worker = *it;
        worker->join();
        delete worker;
    }

    threadList->clear();
}
