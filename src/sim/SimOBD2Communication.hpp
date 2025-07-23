#pragma once

#include <string>

#include "src/interface/IOBD2Communication.hpp"
#include "SimBluetoothConnection.hpp"

class SimOBD2Communication : public IOBD2Communication {
    Q_OBJECT
public:
    SimOBD2Communication(SimBluetoothConnection& bt);
    Q_INVOKABLE bool initialize() override;
    Q_INVOKABLE int getSpeed() override;
    Q_INVOKABLE int getRPM() override;
    Q_INVOKABLE double getThrottlePosition() override;
    Q_INVOKABLE double getOBDSupplyVoltage() override;
    Q_INVOKABLE double getBoostLevel() override;
    Q_INVOKABLE int getCoolantTemperature() override;
    Q_INVOKABLE void queryAllPIDs() override;
    Q_INVOKABLE static void setSpeed(int speedVal);
    Q_INVOKABLE QString getDTCs() override;
    Q_INVOKABLE QString sendCommand(const QString& command) override;

private:
    static int speed;

    Q_INVOKABLE QString parseDTCs(const QString &raw) override;
};