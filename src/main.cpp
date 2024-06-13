#include "BluetoothConnectionSimulator.h"
#include "OBD2CommunicationSimulator.h"

#include <iostream>


int main() {
    BluetoothConnectionSimulator bt;
    if (!bt.connect("COM5")) {
        std::cerr << "Failed to connect to OBD2 device" << std::endl;
        return 1;
    }
    else {
        std::cout << "Connection to OBD2 device successful" << std::endl;
    }

    OBD2CommunicationSimulator obd2(bt);
    if (!obd2.initialize()) {
        std::cerr << "Failed to initialize OBD2 communication" << std::endl;
        return 1;
    }
    else {
        std::cout << "OBD2 communication initialized" << std::endl;
    }

    // Retrieve simulated real-time data

    for(int i = 0; i < 1000; i++){
        auto speed = obd2.getSpeed();
        auto rpm = obd2.getRPM();
        std::cout << "Speed: " << speed << " km/h" << std::endl;
        std::cout << "RPM: " << rpm << std::endl;
    }

    // Retrieve simulated DTCs
    auto dtcs = obd2.getDTCs();
    std::cout << "Diagnostic Trouble Codes: " << dtcs << std::endl;

    return 0;
}