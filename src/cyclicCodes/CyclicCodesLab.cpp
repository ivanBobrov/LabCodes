#include "CyclicCodesLab.h"

CyclicCodesLab::CyclicCodesLab() {

}

CyclicCodesLab::~CyclicCodesLab() {
    delete taskRunner;

    if (!labTaskList->empty()) {
        for (std::vector<CyclicLabTask *>::iterator it = labTaskList->begin(); it < labTaskList->end(); it++) {
            delete (*it);
        }
    }

    delete labTaskList;
}

bool CyclicCodesLab::canStartProcess() {
    return state == CodesLabState::READY;
}

void CyclicCodesLab::startProcess(const std::vector<bool> &inform, const std::vector<bool> &generator,
                                  int experimentsCount, double errorProbability) {
    if (state != CodesLabState::READY) {
        throw std::logic_error("Started send process must be finished to submit new one");
    }

    state = CodesLabState::RUNNING;

    SimplePolynomial informPoly(inform);
    SimplePolynomial genPoly(generator);

    int taskPart = static_cast<int> (std::floor(experimentsCount / taskNumberToRun));

    // First task may have different experiments count
    int firstExperimentsCount = experimentsCount - (taskPart * (taskNumberToRun - 1));
    CyclicLabTask *labTaskFirst = new CyclicLabTask(informPoly, genPoly, firstExperimentsCount, errorProbability);
    labTaskFirst->setOnCompleteListener(this);
    labTaskList->push_back(labTaskFirst);

    for (int i = 1; i < taskNumberToRun; i++) {
        CyclicLabTask *task = new CyclicLabTask(informPoly, genPoly, taskPart, errorProbability);
        task->setOnCompleteListener(this);
        labTaskList->push_back(task);
    }

    for (std::vector<CyclicLabTask *>::iterator it = labTaskList->begin(); it < labTaskList->end(); ++it) {
        CyclicLabTask *task = *it;
        taskRunner->submitTask(*task);
    }
}

CyclicLabResult CyclicCodesLab::getResult() {
    CyclicLabResult result;

    for (std::vector<CyclicLabTask *>::iterator it = labTaskList->begin(); it < labTaskList->end(); ++it) {
        CyclicLabTask *task = *it;
        result.add(task->getResult());
    }

    return result;
}

void CyclicCodesLab::setEventListener(EventListener *listener) {
    this->view = listener;
}

void CyclicCodesLab::onTaskComplete() {
    bool finished = true;
    for (std::vector<CyclicLabTask *>::iterator it = labTaskList->begin(); it < labTaskList->end(); ++it) {
        finished = finished && (*it)->isFinished();
    }

    if (finished) {
        CyclicLabResult labResult = getResult();
        view->onSendProcessFinished(labResult);

        for(std::vector<CyclicLabTask *>::iterator it = labTaskList->begin(); it < labTaskList->end(); ++it) {
            delete *it;
        }
        labTaskList->clear();
        state = CodesLabState::READY;
    }
}

void CyclicCodesLab::setNumberOfThreadsToUse(int threadNumber) {
    if (threadNumber >= 1) {
        taskNumberToRun = threadNumber;
    }
}
