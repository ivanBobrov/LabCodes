#ifndef HAMMING_CODES_ENVIRONMENT_IMITATOR_H
#define HAMMING_CODES_ENVIRONMENT_IMITATOR_H

#include "Message.h"
#include <cstdlib>
#include <ctime>

class EnvironmentImitator {
private:
    static double getRandomDouble(double min, double max);
public:
    static void randomize();
    static int sendMessage(Message &message, double corruptionProbability);
};


#endif //HAMMING_CODES_ENVIRONMENT_IMITATOR_H
