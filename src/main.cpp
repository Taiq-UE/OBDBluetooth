#include "BluetoothConnection.h"
#include "OBD2Communication.h"
#include "BluetoothConnectionSimulator.h"
#include "OBD2CommunicationSimulator.h"
#include "DTC_Codes.h"

#include <iostream>
#include <unordered_map>
#import <sstream>


int main() {

    std::string response = "7E8 04 41 0C 16 04";
    int byteCount = 2;

    size_t start = response.find("41 ");
    if (start == std::string::npos) {
        return -1;
    }

    std::string data = response.substr(start + 6); // Skip "41 " and the next 4 characters
    std::istringstream ss(data);

    std::string byteStr;
    std::string hexValue;
    for (int i = 0; i < byteCount; ++i) {
        if (!(ss >> byteStr)) {
            return -1;
        }
        hexValue += byteStr;
    }

    int value;
    std::istringstream(hexValue) >> std::hex >> value;

    if (byteCount == 2) {
        value = static_cast<int>(value / 4.0); // RPM needs to be divided by 4.0 as per OBD-II spec
    }

    std::cout << "Parsed RPM: " << value << std::endl;



//    BluetoothConnection bt2;
//    if (!bt2.connect("COM5")) {
//        std::cerr << "Failed to connect to OBD2 device" << std::endl;
//    } else {
//        std::cout << "Connection to OBD2 device successful" << std::endl;
//    }
//
//    OBD2Communication obd2(bt2);
//    if (!obd2.initialize()) {
//        std::cerr << "Failed to initialize OBD2 communication" << std::endl;
//    } else {
//        std::cout << "OBD2 communication initialized" << std::endl;
//    }
//
//    // Debugging: print raw responses
//    std::string speedResponse = obd2.sendCommand("010D\r");
//    std::cout << "Raw speed response: " << speedResponse << std::endl;
//
//    std::string rpmResponse = obd2.sendCommand("010C\r");
//    std::cout << "Raw RPM response: " << rpmResponse << std::endl;
//
//    std::cout << "Parsed speed: " << obd2.getSpeed() << std::endl;
//    std::cout << "Parsed RPM: " << obd2.getRPM() << std::endl;
//    std::cout << "DTCs: " << obd2.getDTCs() << std::endl;












//    BluetoothConnectionSimulator bt;
//    if (!bt.connect("COM5")) {
//        std::cerr << "Failed to connect to OBD2 device" << std::endl;
//        return 1;
//    }
//    else {
//        std::cout << "Connection to OBD2 device successful" << std::endl;
//    }
//
//    OBD2CommunicationSimulator obd2(bt);
//    if (!obd2.initialize()) {
//        std::cerr << "Failed to initialize OBD2 communication" << std::endl;
//        return 1;
//    }
//    else {
//        std::cout << "OBD2 communication initialized" << std::endl;
//    }
//
//    // Retrieve simulated real-time data
//
////    for(int i = 0; i < 1000; i++){
////        auto speed = obd2.getSpeed();
////        auto rpm = obd2.getRPM();
////        std::cout << "Speed: " << speed << " km/h" << std::endl;
////        std::cout << "RPM: " << rpm << std::endl;
////    }
//
//    std::string dtcs = obd2.getDTCs();
//    std::cout << "Diagnostic Trouble Codes: " << dtcs << std::endl;
//
//    std::stringstream ss(dtcs);
//    std::string code;
//    std::vector<std::string> codes;
//
//    while (ss >> code) {
//        codes.push_back(code);
//    }
//
//    for (const std::string& code : codes) {
//        auto it = dtcCodes.find(code);
//        if (it != dtcCodes.end()) {
//            std::cout << "Code: " << code << ", " << it->second << std::endl;
//        } else {
//            std::cout << "Code: " << code << ", Unknown DTC code" << std::endl;
//        }
//    }

    return 0;
}