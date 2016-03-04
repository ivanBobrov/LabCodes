#ifndef HAMMING_CODES_HAMMING_LAB_RESULT_H
#define HAMMING_CODES_HAMMING_LAB_RESULT_H


class HammingLabResult {
private:
    int attemptCount;
    int doneAttemptCount;
    int successfullyReceived;
    int repaired;
    int errorMissed;

public:
    HammingLabResult();

    void setAttemptCount(int attemptCount);
    int getAttemptCount() const;
    int getDoneAttemptCount() const;
    void incrementSuccess();
    int getSuccessfullyReceivedCount() const;
    void incrementRepaired();
    int getRepairedCount() const;
    void incrementErrorMissed();
    int getErrorMissedCount() const;

    void clear();

};


#endif //HAMMING_CODES_HAMMING_LAB_RESULT_H
