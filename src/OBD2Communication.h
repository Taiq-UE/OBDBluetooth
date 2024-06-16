#pragma once
#include "BluetoothConnection.h"
#include <string>

class OBD2Communication {
public:
    OBD2Communication(BluetoothConnection& bt);
    virtual bool initialize();
    virtual int getSpeed();
    virtual int getRPM();
    virtual std::string getDTCs();

    std::string sendCommand(const std::string& command);

    static int parseResponse(const std::string &response, int byteCount);

private:
    BluetoothConnection& btConnection;

    int parseResponse(const std::string& response);

};
