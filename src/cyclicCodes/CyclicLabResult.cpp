#include <stdexcept>
#include "CyclicLabResult.h"

CyclicLabResult::CyclicLabResult() : CyclicLabResult(0, 0, 0, 0, 0) { }

CyclicLabResult::CyclicLabResult(int experimentCount, int experimentDone, int receivedCorrectly, int errorDetected,
                                 int missedErrors) {
    this->experimentsCount = experimentCount;
    this->experimentsDone = experimentDone;
    this->receivedCorrectly = receivedCorrectly;
    this->errorDetected = errorDetected;
    this->missedErrors = missedErrors;
}

CyclicLabResult::CyclicLabResult(int experimentCount, int experimentDone, int receivedCorrectly,
                                 int errorDetected, int missedErrors, const std::vector<int> &errorRate) {
    this->experimentsCount = experimentCount;
    this->experimentsDone = experimentDone;
    this->receivedCorrectly = receivedCorrectly;
    this->errorDetected = errorDetected;
    this->missedErrors = missedErrors;
    this->missedErrorRate = errorRate;
}

CyclicLabResult::CyclicLabResult(const CyclicLabResult &origin) {
    this->experimentsCount = origin.experimentsCount;
    this->experimentsDone = origin.experimentsDone;
    this->receivedCorrectly = origin.receivedCorrectly;
    this->errorDetected = origin.errorDetected;
    this->missedErrors = origin.missedErrors;
    this->missedErrorRate = origin.missedErrorRate;
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

int CyclicLabResult::getMissedErrorsUnrated() const {
    return missedErrors;
}

bool CyclicLabResult::isComplete() const {
    return experimentsDone >= experimentsCount;
}

int CyclicLabResult::getMaxRate() const {
    return missedErrorRate.empty() ? 0 : (int) missedErrorRate.size() - 1;
}

int CyclicLabResult::getMissedErrors(int rate) const {
    if (!missedErrorRate.empty() && rate > 0 && rate < missedErrorRate.size()) {
        return missedErrorRate.at((unsigned long) rate);
    }

    return 0;
}

int CyclicLabResult::getMissedErrorsOutOfRate() const {
    if (!missedErrorRate.empty()) {
        return missedErrorRate.at(0);
    }

    return 0;
}

void CyclicLabResult::add(const CyclicLabResult &operand) {
    this->experimentsCount += operand.getExperimentsCount();
    this->experimentsDone += operand.getExperimentsDone();
    this->receivedCorrectly += operand.getReceivedCorrectly();
    this->errorDetected += operand.getErrorDetected();
    this->missedErrors += operand.getMissedErrorsUnrated();

    if (!operand.missedErrorRate.empty()) {
        if (this->missedErrorRate.empty()) {
            this->missedErrorRate = operand.missedErrorRate;
        } else {
            if (missedErrorRate.size() != operand.missedErrorRate.size()) {
                throw std::logic_error("Cyclic lab results error rates sizes must be equal");
            }

            for (unsigned long i = 0; i < missedErrorRate.size(); ++i) {
                this->missedErrorRate.at(i) += operand.missedErrorRate.at(i);
            }
        }
    }
}
