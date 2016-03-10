#include "CyclicCodesLab.h"

CyclicCodesLab::CyclicCodesLab() {

}

void CyclicCodesLab::buttonStartClicked() {
    bool arrOne[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bool arrTwo[] = {1, 1, 0, 1};
    SimplePolynomial polynomialOne(15, arrOne);
    SimplePolynomial polynomialTwo(3, arrTwo);

    LabTaskRunner taskRunner;
    CyclicLabTask labTask1(polynomialOne, polynomialTwo, 20000, 0.0001);
    CyclicLabTask labTask2(polynomialOne, polynomialTwo, 20000, 0.0001);
    CyclicLabTask labTask3(polynomialOne, polynomialTwo, 20000, 0.0001);
    CyclicLabTask labTask4(polynomialOne, polynomialTwo, 20000, 0.0001);
    taskRunner.submitTask(labTask1);
    taskRunner.submitTask(labTask2);
    taskRunner.submitTask(labTask3);
    taskRunner.submitTask(labTask4);
    taskRunner.joinAllThreads();

    CyclicLabResult result = labTask1.getResult();
    result.add(labTask2.getResult());
    result.add(labTask3.getResult());
    result.add(labTask4.getResult());

    std::string label = std::to_string(result.getReceivedCorrectly());

    if (labView != nullptr) {
        labView->setLabel(label);
    }
}

void CyclicCodesLab::setCyclicLabView(CyclicLabView &view) {
    this->labView = &view;
}
