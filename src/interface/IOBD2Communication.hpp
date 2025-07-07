#pragma once
#include <QObject>
#include <string>

class IOBD2Communication : public QObject {
    Q_OBJECT
public:
    virtual ~IOBD2Communication() = default;
    virtual bool initialize() = 0;
    virtual int getSpeed() = 0;
    virtual int getRPM() = 0;
    virtual double getThrottlePosition() = 0;
    virtual double getOBDSupplyVoltage() = 0;
    virtual double getBoostLevel() = 0;
    virtual int getCoolantTemperature() = 0;
    virtual void queryAllPIDs() = 0;
    virtual QString getDTCs() = 0;
    virtual QString parseDTCs(const QString& raw) = 0;
    virtual QString sendCommand(const QString& command) = 0;
};