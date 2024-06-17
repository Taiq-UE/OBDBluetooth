#include "BluetoothConnection.h"
#include "OBD2Communication.h"
#include "BluetoothConnectionSimulator.h"
#include "OBD2CommunicationSimulator.h"
#include "DTC_Codes.h"

#include <iostream>


int main() {
    BluetoothConnection bt2;
    if (!bt2.connect("COM5")) {
        std::cerr << "Failed to connect to OBD2 device" << std::endl;
    } else {
        std::cout << "Connection to OBD2 device successful" << std::endl;
    }

    OBD2Communication obd2(bt2);
    if (!obd2.initialize()) {
        std::cerr << "Failed to initialize OBD2 communication" << std::endl;
    } else {
        std::cout << "OBD2 communication initialized" << std::endl;
    }

    for(int i = 0; i < 1000; i++){
        std::cout << "Speed: " << obd2.getSpeed() << std::endl;
        std::cout << "RPM: " << obd2.getRPM() << std::endl;
        std::cout << "Throttle Position: " << obd2.getThrottlePosition() << std::endl;
        std::cout << "OBD Supply Voltage: " << obd2.getOBDSupplyVoltage() << std::endl;
        std::cout << "Boost Level: " << obd2.getBoostLevel() << std::endl;
        std::cout << "Coolant Temperature: " << obd2.getCoolantTemperature() << std::endl;
    }

    return 0;
}