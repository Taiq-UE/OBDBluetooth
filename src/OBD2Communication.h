#pragma once
#include "BluetoothConnection.h"
#include <string>

class OBD2Communication {
public:
    OBD2Communication(BluetoothConnection& bt);
    bool initialize();
    int getSpeed();
    int getRPM();
    std::string getDTCs();
private:
    BluetoothConnection& btConnection;
    std::string sendCommand(const std::string& command);
    int parseResponse(const std::string& response);
};
