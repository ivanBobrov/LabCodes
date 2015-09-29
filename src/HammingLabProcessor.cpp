#include "HammingLabProcessor.h"

HammingLabProcessor::HammingLabProcessor(HammingCodesLab *hammingCodesLab) {
    this->hammingCodesLab = hammingCodesLab;
    state = HammingLabProcessorState::READY;
}

HammingLabProcessor::~HammingLabProcessor() {
    if (thread != nullptr) {
        if (thread->joinable()) {
            thread->detach(); //TODO: interrupt
        }

        delete thread;
    }

    if (infoMessage != nullptr) {
        delete infoMessage;
    }

    if (codedMessage != nullptr) {
        delete codedMessage;
    }
}

bool HammingLabProcessor::start(const Message* info, double probability, int attemptsCount) {
    if (state == HammingLabProcessorState::READY) {
        state = HammingLabProcessorState::RUNNING;

        this->infoMessage = new Message(*info);
        this->codedMessage = new Message;
        CodeConverter::codeHamming(*infoMessage, *codedMessage);
        this->probability = probability;
        this->attemptsCount = attemptsCount;

        hammingLabResult.clear();
        hammingLabResult.setAttemptCount(attemptsCount);
        thread = new boost::thread(boost::bind(&HammingLabProcessor::execution, this));

        return true;
    } else {
        return false;
    }
}

HammingLabProcessorState HammingLabProcessor::getProcessorState() {
    return state;
}

void HammingLabProcessor::execution() {
    EnvironmentImitator::randomize();
    for (int i = 0; i < attemptsCount; i++) {

        // Create message
        Message probe(*codedMessage);
        Message decoded;

        // Canal corruption
        EnvironmentImitator::sendMessage(probe, probability);

        // Decode
        HammingDecodeStatus status = CodeConverter::decodeHamming(probe, decoded);
        bool equals = infoMessage->equals(decoded);

        if (equals) {
            if (status == HammingDecodeStatus::DECODED) {
                hammingLabResult.incrementSuccess();
            } else if (status == HammingDecodeStatus::REPAIRED) {
                hammingLabResult.incrementRepaired();
            }

        } else {
            hammingLabResult.incrementErrorMissed();
        }

        if (i % 10000 == 0) {
            hammingCodesLab->updateResults(hammingLabResult);
        }
    }

    hammingCodesLab->sendProcessFinished(hammingLabResult);

    thread->detach();
    delete thread;
    thread = nullptr;

    delete infoMessage;
    delete codedMessage;

    state = HammingLabProcessorState::READY;
}
