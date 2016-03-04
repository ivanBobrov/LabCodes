#include "HammingLabEventEmitter.h"


HammingLabEventEmitter::HammingLabEventEmitter() {

}

void HammingLabEventEmitter::onStartProcess() {
    emit startProcessSignal();
}

void HammingLabEventEmitter::onPauseProcess() {
    emit pauseProcessSignal();
}

void HammingLabEventEmitter::onResumeProcess() {
    emit resumeProcessSignal();
}

void HammingLabEventEmitter::onInformationMessageChanged(std::vector<bool> &infoMessage,
                                                         std::vector<bool> &codedMessage) {
    emit informationMessageChangedSignal(infoMessage, codedMessage);
}

void HammingLabEventEmitter::onProbabilityChanged(double newProbability) {
    emit probabilityChangedSignal(newProbability);
}

void HammingLabEventEmitter::onAttemptsCountChanged(int newAttemptsCount) {
    emit attemptsCountChangedSignal(newAttemptsCount);
}

void HammingLabEventEmitter::onResultsChanged(HammingLabResult &results) {
    emit resultsChangedSignal(results);
}

void HammingLabEventEmitter::onSendProcessFinished(HammingLabResult &results) {
    emit sendProcessFinishedSignal(results);
}
