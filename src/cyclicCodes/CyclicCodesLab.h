#ifndef HAMMING_CODES_CYCLIC_CODES_LAB_H
#define HAMMING_CODES_CYCLIC_CODES_LAB_H

#include <Polynomial.h>
#include <SimplePolynomial.h>
#include <Message.h>
#include <CodeConverter.h>
#include <vector>
#include "LabTaskRunner.h"
#include "CyclicLabTask.h"

class ICyclicCodesLab {
public:

    /**
     * @return true if cyclicCodesLab object is ready to start send process.
     */
    virtual bool canStartProcess() = 0;

    /**
     * @return true if send process started and not yet finished.
     */
    virtual bool isRunning() = 0;

    /**
     * Starts send process for correspondence information and generator
     * polynomials. Make sure <code>inform</code> and <code>generator</code>
     * vectors are stored in little-endian format i.e. lower power first.
     *
     * @param inform reference to information array
     * @param generator reference to generator array
     * @param experimentsCount number of experiments to be done
     * @param errorProbability probability of switching each particularly bit
     *        during send process.
     */
    virtual void startProcess(const std::vector<bool> &inform, const std::vector<bool> &generator,
                              int experimentsCount, double errorProbability) = 0;

    /**
     * Method immediately stops send process and removes results. It fires
     * <code>EventListener::onBreakProcess</code> event with last obtained
     * results as a parameter after interrupting running tasks and joining all
     * threads.
     */
    virtual void breakProcess() = 0;

    /**
     * Method for obtaining lab results. It returns result object even if send
     * process hasn't finished yet. In this case result will represent current
     * status of send process.
     *
     * @return laboratory experiment results
     */
    virtual CyclicLabResult getResult() = 0;

    /**
     * EventListener is an interface for subscribing to lab events.
     */
    class EventListener {
    public:

        /**
         * Event fires when all experiments are done. After that methods
         * <code>getResult()</code> will no longer provide information about
         * current task.
         *
         * @param result final experiment statistics
         */
        virtual void onSendProcessFinished(CyclicLabResult result) = 0;

        /**
         * Event fires when model needs to view status or any other information
         * to user.
         *
         * @param label textual information
         */
        virtual void setInfo(std::string label) = 0;

        /**
         * Event fires after all tasks are interrupted and threads joined.
         *
         * @param lastObtainedResult
         */
        virtual void onBreakProcess(CyclicLabResult lastObtainedResult) = 0;
    };


    virtual void setEventListener(EventListener *listener) = 0;
};

enum class CodesLabState {
    READY,
    RUNNING
};

class CyclicCodesLab : public ICyclicCodesLab, public LabTask::OnCompleteListener {
private:
    int taskNumberToRun = 1;
    CodesLabState state = CodesLabState::READY;
    EventListener *view = nullptr;
    LabTaskRunner *taskRunner = new LabTaskRunner;
    std::vector<CyclicLabTask *> *labTaskList = new std::vector<CyclicLabTask *>;

public:
    CyclicCodesLab();
    ~CyclicCodesLab();

    virtual bool canStartProcess();
    virtual bool isRunning();
    virtual void startProcess(const std::vector<bool> &inform, const std::vector<bool> &generator,
                              int experimentsCount, double errorProbability);
    virtual void breakProcess();
    virtual CyclicLabResult getResult();
    virtual void setEventListener(EventListener *listener);

    virtual void onTaskComplete();

    void setNumberOfThreadsToUse(int threadNumber);
};


#endif //HAMMING_CODES_CYCLIC_CODES_LAB_H
