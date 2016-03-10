#include "EnvironmentImitator.h"


void EnvironmentImitator::randomize() {
    std::srand(std::time(0));
}

int EnvironmentImitator::sendMessage(Message &message, double corruptionProbability) {
    int errorCount = 0;

    for (int i = 0; i < message.size(); i++) {
        double random = getRandomDouble(0, 1);
        if (random < corruptionProbability) {
            message.switchBit(i);
            errorCount++;
        }
    }

    return errorCount;
}


double EnvironmentImitator::getRandomDouble(double min, double max) {
    double random = (double) std::rand() / RAND_MAX;
    return min + random * (max - min);
}
