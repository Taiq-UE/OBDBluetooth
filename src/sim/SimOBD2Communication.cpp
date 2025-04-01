#include <QThread>

#include "SimOBD2Communication.hpp"

int SimOBD2Communication::speed = 0;
SimOBD2Communication::SimOBD2Communication(SimBluetoothConnection& bt) {

}

bool SimOBD2Communication::initialize() {
    // Simulated initialization logic
    return true;
}

int SimOBD2Communication::getSpeed() {
    return speed++;
}

void SimOBD2Communication::setSpeed(int speedVal) {
    speed = speedVal;
}

int SimOBD2Communication::getRPM() {
    // Simulated RPM value
    return 3000;
}

double SimOBD2Communication::getThrottlePosition() {
    // Simulated throttle position
    return 25.0;
}

double SimOBD2Communication::getOBDSupplyVoltage() {
    // Simulated OBD supply voltage
    return 12.5;
}

double SimOBD2Communication::getBoostLevel() {
    // Simulated boost level
    return 1.2;
}

int SimOBD2Communication::getCoolantTemperature() {
    // Simulated coolant temperature
    return 90;
}

void SimOBD2Communication::queryAllPIDs() {
    // Simulated query all PIDs
}

QString SimOBD2Communication::getDTCs() {
    // Simulated DTCs
    return "P0001, P1002, P2003";
}

QString SimOBD2Communication::sendCommand(const QString& command) {
    // Simulated command response
    return "41 0C 1A F8";
}