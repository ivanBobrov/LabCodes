#ifndef CODES_CODE_CONVERTER_H
#define CODES_CODE_CONVERTER_H

#include <math.h>
#include "Message.h"

enum class HammingDecodeStatus {
    DECODED,
    REPAIRED,
};

class CodeConverter {
private:
    static bool XOR(bool a, bool b);
    static bool repairHammingMessage(Message &message);

public:
    static void codeHamming(const Message& origin, Message& output);
    static HammingDecodeStatus decodeHamming(Message &coded, Message &decodedOutput);
};


#endif //CODES_CODE_CONVERTER_H
