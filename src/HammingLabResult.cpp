#include "HammingLabResult.h"


HammingLabResult::HammingLabResult() {
    this->attemptCount = 0;
    this->doneAttemptCount = 0;
    this->successfullyReceived = 0;
    this->repaired = 0;
    this->errorMissed = 0;
}

void HammingLabResult::setAttemptCount(int attemptCount) {
    this->attemptCount = attemptCount;
}

void HammingLabResult::incrementSuccess() {
    doneAttemptCount++;
    successfullyReceived++;
}

void HammingLabResult::incrementRepaired() {
    doneAttemptCount++;
    repaired++;
}

void HammingLabResult::incrementErrorMissed() {
    doneAttemptCount++;
    errorMissed++;
}

int HammingLabResult::getAttemptCount() const {
    return attemptCount;
}

int HammingLabResult::getDoneAttemptCount() const {
    return doneAttemptCount;
}

int HammingLabResult::getSuccessfullyReceivedCount() const {
    return successfullyReceived;
}

int HammingLabResult::getRepairedCount() const {
    return repaired;
}

int HammingLabResult::getErrorMissedCount() const {
    return errorMissed;
}

void HammingLabResult::clear() {
    doneAttemptCount = 0;
    successfullyReceived = 0;
    repaired = 0;
    errorMissed = 0;

}
