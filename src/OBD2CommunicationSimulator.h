#pragma once
#include "OBD2Communication.h"
#include <random>

class OBD2CommunicationSimulator : public OBD2Communication {
public:
    OBD2CommunicationSimulator(BluetoothConnection& bt);
    bool initialize() override;
    int getSpeed() override;
    int getRPM() override;
    std::string getDTCs() override;

private:
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
};