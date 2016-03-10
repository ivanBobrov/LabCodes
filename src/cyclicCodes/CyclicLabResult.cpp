#include "CyclicLabResult.h"


CyclicLabResult::CyclicLabResult(int experimentCount, int experimentDone, int receivedCorrectly,
                                 int errorDetected, int missedErrors) {
    this->experimentsCount = experimentCount;
    this->experimentsDone = experimentDone;
    this->receivedCorrectly = receivedCorrectly;
    this->errorDetected = errorDetected;
    this->missedErrors = missedErrors;
}

int CyclicLabResult::getExperimentsCount() const {
    return experimentsCount;
}

int CyclicLabResult::getExperimentsDone() const {
    return experimentsDone;
}

int CyclicLabResult::getReceivedCorrectly() const {
    return receivedCorrectly;
}

int CyclicLabResult::getErrorDetected() const {
    return errorDetected;
}

int CyclicLabResult::getMissedErrors() const {
    return missedErrors;
}

bool CyclicLabResult::isComplete() const {
    return experimentsDone >= experimentsCount;
}

void CyclicLabResult::add(const CyclicLabResult &operand) {
    this->experimentsCount += operand.getExperimentsCount();
    this->experimentsDone += operand.getExperimentsDone();
    this->receivedCorrectly += operand.getReceivedCorrectly();
    this->errorDetected += operand.getErrorDetected();
    this->missedErrors += operand.getMissedErrors();
}
