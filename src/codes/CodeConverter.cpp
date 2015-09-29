#include "CodeConverter.h"

void CodeConverter::codeHamming(const Message &origin, Message &output) {
    output.clear();

    int infoBitsCount = origin.size();
    int controlBitsCount = (int)(ceil(log2(infoBitsCount))) + 1;
    int outputBitsCount = infoBitsCount + controlBitsCount;

    int nextControlIndex = 1;
    int infoIndex = 0;
    for (int i = 0; i < outputBitsCount; i++) {
        if (i == nextControlIndex - 1) {
            output.appendBit(false);
            nextControlIndex *=2;
        } else {
            output.appendBit(origin.getBit(infoIndex++));
        }
    }

    for (nextControlIndex = 1; nextControlIndex <= pow(2, controlBitsCount); nextControlIndex *= 2) {
        int controlIndex = nextControlIndex - 1;
        bool bitValue = false;

        int index = controlIndex;
        while (index < outputBitsCount) {
            for (int i = 0; i < nextControlIndex && index < outputBitsCount; i++) {
                bitValue = XOR(bitValue, output.getBit(index++));
            }
            index += nextControlIndex;
        }

        output.setBit(controlIndex, bitValue);
    }
}

HammingDecodeStatus CodeConverter::decodeHamming(Message &coded, Message &decodedOutput) {
    decodedOutput.clear();
    bool repaired = repairHammingMessage(coded);

    int controlNumber = 1;
    for (int i = 0; i < coded.size(); i++) {
        if (i != controlNumber - 1) {
            decodedOutput.appendBit(coded.getBit(i));
        } else {
            controlNumber *= 2;
        }
    }

    return repaired ? HammingDecodeStatus::REPAIRED : HammingDecodeStatus::DECODED;
}


bool CodeConverter::XOR(bool a, bool b) {
    return ((!a) != (!b));
}

bool CodeConverter::repairHammingMessage(Message &message) {
    int repairElementIndex = 0;
    for (int controlNumber = 1; controlNumber < message.size(); controlNumber *= 2) {
        int controlIndex = controlNumber - 1;
        bool bitValue = false;

        int currentIndex = controlIndex;
        while (currentIndex < message.size()) {
            for (int j = 0; j < controlNumber && currentIndex < message.size(); j++) {
                bitValue = XOR(bitValue, message.getBit(currentIndex++));
            }
            currentIndex += controlNumber;
        }

        if (bitValue) {
            repairElementIndex += controlNumber;
        }
    }

    if (repairElementIndex != 0) {
        message.switchBit(repairElementIndex - 1);
        return true;
    }

    return false;
}
