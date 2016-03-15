#ifndef HAMMING_CODES_CYCLIC_LAB_TASK_H
#define HAMMING_CODES_CYCLIC_LAB_TASK_H

#include <boost/thread/thread.hpp>
#include <Polynomial.h>
#include <SimplePolynomial.h>
#include <CodeConverter.h>
#include <EnvironmentImitator.h>
#include "LabTaskRunner.h"
#include "CyclicLabResult.h"

class CyclicLabTask : public LabTask {

private:
    Polynomial *information;
    Polynomial *generator;
    int experimentCount;
    double errorProbability;

    int experimentDone = 0;
    int receivedCorrectly = 0;
    int errorDetected = 0;
    int missedError = 0;

    bool interruptionFlag = false;
    boost::mutex statisticsMutex;
    boost::mutex interruptionMutex;

public:
    CyclicLabTask(const Polynomial &information, const Polynomial &generator,
                  int experimentCount, double errorProbability);
    CyclicLabTask(const CyclicLabTask& origin);
    ~CyclicLabTask();

    virtual void task();
    CyclicLabResult getResult();
    void interrupt();
};


#endif //HAMMING_CODES_CYCLIC_LAB_TASK_H
