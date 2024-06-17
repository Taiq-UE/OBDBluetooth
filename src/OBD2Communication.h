#pragma once
#include "BluetoothConnection.h"
#include <string>

class OBD2Communication {
public:
    OBD2Communication(BluetoothConnection& bt);
    virtual bool initialize();
    virtual int getSpeed();
    virtual int getRPM();
    virtual double getThrottlePosition();
    virtual std::string getDTCs();

    std::string sendCommand(const std::string& command);

    static int parseResponse(const std::string &response, int byteCount);

    void checkSupportedPIDs();

    double getBoostPressure();

    double getBoostPressureSpecifiedValue();

    double getBoostPressureActualValue();

    void queryAllPIDs();

private:
    BluetoothConnection& btConnection;

    int parseResponse(const std::string& response);

    void parseAndPrintResponse(const std::string &command, const std::string &response);
};
