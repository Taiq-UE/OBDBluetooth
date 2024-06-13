#include "BluetoothConnection.h"
#include "OBD2Communication.h"

#include <iostream>

int main() {
    BluetoothConnection bt;
    if (!bt.connect("COM5")) {
        std::cerr << "Failed to connect to OBD2 device" << std::endl;
        return 1;
    }

    OBD2Communication obd2(bt);
    if (!obd2.initialize()) {
        std::cerr << "Failed to initialize OBD2 communication" << std::endl;
        return 1;
    }

    // Retrieve real-time data
    auto speed = obd2.getSpeed();
    auto rpm = obd2.getRPM();
    std::cout << "Speed: " << speed << " km/h" << std::endl;
    std::cout << "RPM: " << rpm << std::endl;

    // Retrieve DTCs
    auto dtcs = obd2.getDTCs();
    std::cout << "Diagnostic Trouble Codes: " << dtcs << std::endl;

    return 0;
}
