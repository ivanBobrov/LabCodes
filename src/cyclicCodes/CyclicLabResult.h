#ifndef HAMMING_CODES_CYCLIC_LAB_RESULT_H
#define HAMMING_CODES_CYCLIC_LAB_RESULT_H


class CyclicLabResult {
private:
    int experimentsCount;
    int experimentsDone;
    int receivedCorrectly;
    int errorDetected;
    int missedErrors;

public:
    CyclicLabResult(int experimentCount, int experimentDone, int receivedCorrectly,
                    int errorDetected, int missedErrors);

    int getExperimentsCount() const;

    int getExperimentsDone() const;

    int getReceivedCorrectly() const;

    int getErrorDetected() const;

    int getMissedErrors() const;

    bool isComplete() const;

    void add(const CyclicLabResult &operand);
};


#endif //HAMMING_CODES_CYCLIC_LAB_RESULT_H
