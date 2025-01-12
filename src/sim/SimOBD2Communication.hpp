#pragma once

#include <string>

#include "src/interface/IOBD2Communication.hpp"

class SimOBD2Communication : public IOBD2Communication {
    Q_OBJECT
public:
    Q_INVOKABLE bool initialize() override;
    Q_INVOKABLE int getSpeed() override;
    Q_INVOKABLE int getRPM() override;
    Q_INVOKABLE double getThrottlePosition() override;
    Q_INVOKABLE double getOBDSupplyVoltage() override;
    Q_INVOKABLE double getBoostLevel() override;
    Q_INVOKABLE int getCoolantTemperature() override;
    Q_INVOKABLE void queryAllPIDs() override;
    Q_INVOKABLE QString getDTCs() override;
    Q_INVOKABLE QString sendCommand(const QString& command) override;
};