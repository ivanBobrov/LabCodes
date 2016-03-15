#ifndef HAMMING_CODES_CYCLIC_LAB_RESULT_H
#define HAMMING_CODES_CYCLIC_LAB_RESULT_H

#include <vector>

class CyclicLabResult {
private:
    int experimentsCount;
    int experimentsDone;
    int receivedCorrectly;
    int errorDetected;
    int missedErrors;
    std::vector<int> missedErrorRate;

public:
    CyclicLabResult();
    CyclicLabResult(int experimentCount, int experimentDone, int receivedCorrectly,
                    int errorDetected, int missedErrors);
    CyclicLabResult(int experimentCount, int experimentDone, int receivedCorrectly,
                    int errorDetected, int missedErrors, const std::vector<int> &errorRate);
    CyclicLabResult(const CyclicLabResult &origin);

    int getExperimentsCount() const;

    int getExperimentsDone() const;

    int getReceivedCorrectly() const;

    int getErrorDetected() const;

    int getMissedErrorsUnrated() const;

    int getMaxRate() const;

    int getMissedErrors(int rate) const;

    int getMissedErrorsOutOfRate() const;

    bool isComplete() const;

    void add(const CyclicLabResult &operand);
};


#endif //HAMMING_CODES_CYCLIC_LAB_RESULT_H
