#include "CyclicLabTask.h"

CyclicLabTask::CyclicLabTask(const Polynomial &information, const Polynomial &generator,
                             int experimentCount, double errorProbability) {
    this->information = new SimplePolynomial(information);
    this->generator = new SimplePolynomial(generator);
    this->experimentCount = experimentCount;
    this->errorProbability = errorProbability;
}

CyclicLabTask::CyclicLabTask(const CyclicLabTask &origin) {
    this->information = new SimplePolynomial(*origin.information);
    this->generator = new SimplePolynomial(*origin.generator);
    this->experimentCount = origin.experimentCount;
    this->errorProbability = origin.errorProbability;
}

CyclicLabTask::~CyclicLabTask() {
    delete information;
    delete generator;
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
            }
        } else {
            errorDetected++;
        }

        statisticsMutex.unlock();
    }
}

CyclicLabResult CyclicLabTask::getResult() {
    statisticsMutex.lock();
    CyclicLabResult labResult(experimentCount, experimentDone, receivedCorrectly, errorDetected, missedError);
    statisticsMutex.unlock();

    return labResult;
}
