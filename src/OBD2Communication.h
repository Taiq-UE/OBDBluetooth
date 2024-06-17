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
    virtual std::string getOBDSupplyVoltage();
    virtual double getBoostLevel();
    virtual int getCoolantTemperature();
    virtual void queryAllPIDs();
    virtual std::string getDTCs();
    std::string sendCommand(const std::string& command);

private:
    BluetoothConnection& btConnection;

    static void parseAndPrintResponse(const std::string &command, const std::string &response);
};
