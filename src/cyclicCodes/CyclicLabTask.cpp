#include "CyclicLabTask.h"

CyclicLabTask::CyclicLabTask(const Polynomial &information, const Polynomial &generator,
                             int experimentCount, double errorProbability) {
    this->information = new SimplePolynomial(information);
    this->generator = new SimplePolynomial(generator);
    this->experimentCount = experimentCount;
    this->errorProbability = errorProbability;
    this->missedErrorRate = new std::vector<int>(MISSED_ERROR_RATE_COUNT);
}

CyclicLabTask::CyclicLabTask(const CyclicLabTask &origin) {
    this->information = new SimplePolynomial(*origin.information);
    this->generator = new SimplePolynomial(*origin.generator);
    this->experimentCount = origin.experimentCount;
    this->errorProbability = origin.errorProbability;
    this->missedErrorRate = new std::vector<int>(*origin.missedErrorRate);
}

CyclicLabTask::~CyclicLabTask() {
    delete information;
    delete generator;
    delete missedErrorRate;
}

void CyclicLabTask::task() {
    Message codedMessage = CodeConverter::codeCRC(*information, *generator);
    EnvironmentImitator::randomize();

    for (int attempt = 1; attempt <= experimentCount; attempt++ ) {
        Message probe(codedMessage);
        int errorCount = EnvironmentImitator::sendMessage(probe, errorProbability);

        bool correct = CodeConverter::checkCorrectnessCRC(probe, *generator);
        bool equals = information->equals(CodeConverter::extractCRC(probe, *generator));

        statisticsMutex.lock();

        experimentDone++;
        if (correct) {
            if (equals) {
                receivedCorrectly++;
            } else {
                missedError++;
                unsigned long missedErrorRateIndex = errorCount < MISSED_ERROR_RATE_COUNT ?
                                                     (unsigned long) errorCount : 0;
                missedErrorRate->at(missedErrorRateIndex)++;
            }
        } else {
            errorDetected++;
        }

        statisticsMutex.unlock();

        interruptionMutex.lock();
        bool interrupt = interruptionFlag;
        interruptionMutex.unlock();

        if (interrupt) {
            throw boost::thread_interrupted();
        }
    }
}

CyclicLabResult CyclicLabTask::getResult() {
    statisticsMutex.lock();
    CyclicLabResult labResult(experimentCount, experimentDone, receivedCorrectly,
                              errorDetected, missedError, *missedErrorRate);
    statisticsMutex.unlock();

    return labResult;
}

void CyclicLabTask::interrupt() {
    boost::lock_guard<boost::mutex> lock(interruptionMutex);
    interruptionFlag = true;
}
