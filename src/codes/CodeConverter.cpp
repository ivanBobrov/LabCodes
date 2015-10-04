#include "CodeConverter.h"

void CodeConverter::codeHamming(const Message &origin, Message &output) {
    output.clear();

    int infoBitsCount = origin.size();
    if (infoBitsCount == 0) {
        return;
    }

    // Add control bits in the required place
    {
        int currentControlBitIndex = 0;
        int currentOriginMessageIndex = 0;
        int currentOutputMessageIndex = 0;
        while (currentOriginMessageIndex < infoBitsCount) {
            if (currentOutputMessageIndex == currentControlBitIndex) {
                output.appendBit(false);
                currentControlBitIndex = (((currentControlBitIndex + 1) * 2) - 1);
            } else {
                output.appendBit(origin.getBit(currentOriginMessageIndex));
                currentOriginMessageIndex++;
            }

            currentOutputMessageIndex++;
        }
    }

    // Fill control bits
    {
        int currentControlBitIndex = 0;
        while (currentControlBitIndex < output.size()) {
            bool bitValue = false;
            int index = currentControlBitIndex;
            while (index < output.size()) {
                for (int i = 0; i < currentControlBitIndex + 1; i++) {
                    bitValue = XOR(bitValue, output.getBit(index + i));
                }

                index += (currentControlBitIndex + 1) * 2;
            }

            output.setBit(currentControlBitIndex, bitValue);
            currentControlBitIndex = (((currentControlBitIndex + 1) * 2) - 1);
        }
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
