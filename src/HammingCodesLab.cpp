#include "HammingCodesLab.h"

std::vector<bool> HammingCodesLab::DEFAULT_INFORMATION_MESSAGE = {true, false, true, false, true};
const double HammingCodesLab::DEFAULT_PROBABILITY = 0.0001;
const int HammingCodesLab::DEFAULT_ATTEMPTS_COUNT = 5000000;

HammingCodesLab::HammingCodesLab(HammingLabView *hammingLabView) {
    this->hammingLabView = hammingLabView;
    this->information = new Message;
    this->codedMessage = new Message;
}

HammingCodesLab *HammingCodesLab::createInstance(HammingLabView *hammingLabView) {
    HammingCodesLab* lab = new HammingCodesLab(hammingLabView);

    lab->hammingLabProcessor = new HammingLabProcessor(lab);

    lab->setInformationMessage(DEFAULT_INFORMATION_MESSAGE);
    lab->setProbability(DEFAULT_PROBABILITY);
    lab->setAttemptsCount(DEFAULT_ATTEMPTS_COUNT);

    return lab;
}

HammingCodesLab::~HammingCodesLab() {
    delete information;
    delete codedMessage;
    delete hammingLabProcessor;
}

void HammingCodesLab::startSendProcess() {
    hammingLabView->onStartProcess();
    if (hammingLabProcessor->getProcessorState() == HammingLabProcessorState::READY) {
        hammingLabProcessor->start(information, corruptionProbability, attemptsCount);
    }
}

void HammingCodesLab::pauseSendProcess() {
    hammingLabProcessor->pause();
    hammingLabView->onPauseProcess();
}

void HammingCodesLab::resumeSendProcess() {
    hammingLabProcessor->resume();
    hammingLabView->onResumeProcess();
}

void HammingCodesLab::stopSendProcess() {
    hammingLabProcessor->stop();
}

void HammingCodesLab::setInformationMessage(std::vector<bool> &infoMessage) {
    if (infoMessage.empty()) {
        information->clear();
        codedMessage->clear();
    } else {
        information->clear();
        for (std::vector<bool>::reverse_iterator it = infoMessage.rbegin(); it != infoMessage.rend(); it++) {
            information->appendBit(*it);
        }

        CodeConverter::codeHamming(*information, *codedMessage);
    }


    std::vector<bool> codedVector = codedMessage->toBoolVector();
    hammingLabView->onInformationMessageChanged(infoMessage, codedVector);
}

void HammingCodesLab::setProbability(double probability) {
    if (probability < 0 || probability > 1) {
        //TODO: incorrect input
        return;
    }

    corruptionProbability = probability;
    hammingLabView->onProbabilityChanged(probability);
}

void HammingCodesLab::setAttemptsCount(int count) {
    if (count < 0) {
        //TODO: incorrect input
        return;
    }

    attemptsCount = count;
    hammingLabView->onAttemptsCountChanged(count);
}

void HammingCodesLab::updateResults(HammingLabResult &results) {
    hammingLabView->onResultsChanged(results);
}


void HammingCodesLab::sendProcessFinished(HammingLabResult &results) {
    hammingLabView->onResultsChanged(results);
    hammingLabView->onSendProcessFinished(results);
}
