#include "OBD2Communication.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>


OBD2Communication::OBD2Communication(BluetoothConnection& bt) : btConnection(bt) {}

struct PID {
    std::string description;
    int length;
    std::string unit;
};

std::map<std::string, PID> pidDetails = {
        {"0100", {"PIDs supported [01-20]", 4, ""}},
        {"0101", {"Monitor status since DTCs cleared", 4, ""}},
        {"0102", {"Freeze DTC", 2, ""}},
        {"0103", {"Fuel system status", 2, ""}},
        {"0104", {"Calculated engine load", 1, "%"}},
        {"0105", {"Engine coolant temperature", 1, "°C"}},
        {"0106", {"Short term fuel trim—Bank 1", 1, "%"}},
        {"0107", {"Long term fuel trim—Bank 1", 1, "%"}},
        {"0108", {"Short term fuel trim—Bank 2", 1, "%"}},
        {"0109", {"Long term fuel trim—Bank 2", 1, "%"}},
        {"010A", {"Fuel pressure", 1, "kPa"}},
        {"010B", {"Intake manifold absolute pressure", 1, "kPa"}},
        {"010C", {"Engine RPM", 2, "rpm"}},
        {"010D", {"Vehicle speed", 1, "km/h"}},
        {"010E", {"Timing advance", 1, "°"}},
        {"010F", {"Intake air temperature", 1, "°C"}},
        {"0110", {"MAF air flow rate", 2, "g/s"}},
        {"0111", {"Throttle position", 1, "%"}},
        {"0112", {"Commanded secondary air status", 1, ""}},
        {"0113", {"Oxygen sensors present (2 banks)", 1, ""}},
        {"0114", {"Oxygen Sensor 1 A: Voltage, Short term fuel trim", 2, "V"}},
        {"0115", {"Oxygen Sensor 2 A: Voltage, Short term fuel trim", 2, "V"}},
        {"0116", {"Oxygen Sensor 3 A: Voltage, Short term fuel trim", 2, "V"}},
        {"0117", {"Oxygen Sensor 4 A: Voltage, Short term fuel trim", 2, "V"}},
        {"0118", {"Oxygen Sensor 5 A: Voltage, Short term fuel trim", 2, "V"}},
        {"0119", {"Oxygen Sensor 6 A: Voltage, Short term fuel trim", 2, "V"}},
        {"011A", {"Oxygen Sensor 7 A: Voltage, Short term fuel trim", 2, "V"}},
        {"011B", {"Oxygen Sensor 8 A: Voltage, Short term fuel trim", 2, "V"}},
        {"011C", {"OBD standards this vehicle conforms to", 1, ""}},
        {"011D", {"Oxygen sensors present (4 banks)", 1, ""}},
        {"011E", {"Auxiliary input status", 1, ""}},
        {"011F", {"Run time since engine start", 2, "s"}},
        {"0120", {"PIDs supported [21-40]", 4, ""}},
        {"0121", {"Distance traveled with malfunction indicator lamp (MIL) on", 2, "km"}},
        {"0122", {"Fuel Rail Pressure (relative to manifold vacuum)", 2, "kPa"}},
        {"0123", {"Fuel Rail Pressure (diesel, or gasoline direct inject)", 2, "kPa"}},
        {"0124", {"Oxygen Sensor 1 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0125", {"Oxygen Sensor 2 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0126", {"Oxygen Sensor 3 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0127", {"Oxygen Sensor 4 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0128", {"Oxygen Sensor 5 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0129", {"Oxygen Sensor 6 B: Voltage, Short term fuel trim", 2, "V"}},
        {"012A", {"Oxygen Sensor 7 B: Voltage, Short term fuel trim", 2, "V"}},
        {"012B", {"Oxygen Sensor 8 B: Voltage, Short term fuel trim", 2, "V"}},
        {"012C", {"Commanded EGR", 1, "%"}},
        {"012D", {"EGR Error", 1, "%"}},
        {"012E", {"Commanded evaporative purge", 1, "%"}},
        {"012F", {"Fuel Tank Level Input", 1, "%"}},
        {"0130", {"Warm-ups since codes cleared", 1, ""}},
        {"0131", {"Distance traveled since codes cleared", 2, "km"}},
        {"0132", {"Evaporative system vapor pressure", 2, "Pa"}},
        {"0133", {"Barometric pressure", 1, "kPa"}},
        {"0134", {"Oxygen Sensor 1 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0135", {"Oxygen Sensor 2 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0136", {"Oxygen Sensor 3 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0137", {"Oxygen Sensor 4 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0138", {"Oxygen Sensor 5 B: Voltage, Short term fuel trim", 2, "V"}},
        {"0139", {"Oxygen Sensor 6 B: Voltage, Short term fuel trim", 2, "V"}},
        {"013A", {"Oxygen Sensor 7 B: Voltage, Short term fuel trim", 2, "V"}},
        {"013B", {"Oxygen Sensor 8 B: Voltage, Short term fuel trim", 2, "V"}},
        {"013C", {"Catalyst Temperature: Bank 1, Sensor 1", 2, "°C"}},
        {"013D", {"Catalyst Temperature: Bank 2, Sensor 1", 2, "°C"}},
        {"013E", {"Catalyst Temperature: Bank 1, Sensor 2", 2, "°C"}},
        {"013F", {"Catalyst Temperature: Bank 2, Sensor 2", 2, "°C"}},
        {"0140", {"PIDs supported [41-60]", 4, ""}},
        {"0141", {"Monitor status this drive cycle", 4, ""}},
        {"0142", {"Control module voltage", 2, "V"}},
        {"0143", {"Absolute load value", 2, "%"}},
        {"0144", {"Commanded equivalence ratio", 2, ""}},
        {"0145", {"Relative throttle position", 1, "%"}},
        {"0146", {"Ambient air temperature", 1, "°C"}},
        {"0147", {"Absolute throttle position B", 1, "%"}},
        {"0148", {"Absolute throttle position C", 1, "%"}},
        {"0149", {"Accelerator pedal position D", 1, "%"}},
        {"014A", {"Accelerator pedal position E", 1, "%"}},
        {"014B", {"Accelerator pedal position F", 1, "%"}},
        {"014C", {"Commanded throttle actuator", 1, "%"}},
        {"014D", {"Time run with MIL on", 2, "min"}},
        {"014E", {"Time since trouble codes cleared", 2, "min"}},
        {"014F", {"Maximum value for equivalence ratio, oxygen sensor voltage, oxygen sensor current, and intake manifold absolute pressure", 2, ""}},
        {"0150", {"Maximum value for air flow rate from mass air flow sensor", 2, "g/s"}},
        {"0151", {"Fuel Type", 1, ""}},
        {"0152", {"Ethanol fuel %", 1, "%"}},
        {"0153", {"Absolute Evap system Vapor Pressure", 2, "kPa"}},
        {"0154", {"Evap system vapor pressure", 2, "Pa"}},
        {"0155", {"Short term secondary oxygen sensor trim—Bank 1", 1, "%"}},
        {"0156", {"Long term secondary oxygen sensor trim—Bank 1", 1, "%"}},
        {"0157", {"Short term secondary oxygen sensor trim—Bank 2", 1, "%"}},
        {"0158", {"Long term secondary oxygen sensor trim—Bank 2", 1, "%"}},
        {"0159", {"Fuel rail pressure (absolute)", 2, "kPa"}},
        {"015A", {"Relative accelerator pedal position", 1, "%"}},
        {"015B", {"Hybrid battery pack remaining life", 1, "%"}},
        {"015C", {"Engine oil temperature", 1, "°C"}},
        {"015D", {"Fuel injection timing", 2, "°"}},
        {"015E", {"Engine fuel rate", 2, "L/h"}},
        {"015F", {"Emission requirements to which vehicle is designed", 1, ""}},
        {"0160", {"PIDs supported [61-80]", 4, ""}},
        {"0161", {"Driver's demand engine - percent torque", 1, "%"}},
        {"0162", {"Actual engine - percent torque", 1, "%"}},
        {"0163", {"Engine reference torque", 2, "Nm"}},
        {"0164", {"Engine percent torque data", 5, "%"}},
        {"0165", {"Auxiliary input/output supported", 4, ""}},
        {"0166", {"Mass air flow sensor", 2, "g/s"}},
        {"0167", {"Engine coolant temperature", 1, "°C"}},
        {"0168", {"Intake air temperature", 1, "°C"}},
        {"0169", {"Throttle position", 1, "%"}},
        {"016A", {"Fuel pressure", 1, "kPa"}},
        {"016B", {"Barometric pressure", 1, "kPa"}},
        {"016C", {"Commanded evaporative purge", 1, "%"}},
        {"016D", {"Fuel level input", 1, "%"}},
        {"016E", {"Ambient air temperature", 1, "°C"}},
        {"016F", {"Time run with MIL on", 2, "min"}},
        {"0170", {"Time since trouble codes cleared", 2, "min"}},
        {"0171", {"Maximum value for equivalence ratio", 2, ""}},
        {"0172", {"Maximum value for air flow rate", 2, "g/s"}},
        {"0173", {"Fuel Type", 1, ""}},
        {"0174", {"Ethanol fuel %", 1, "%"}},
        {"0175", {"Absolute Evap system vapor pressure", 2, "kPa"}},
        {"0176", {"Evap system vapor pressure", 2, "Pa"}},
        {"0177", {"Short term secondary oxygen sensor trim—Bank 1", 1, "%"}},
        {"0178", {"Long term secondary oxygen sensor trim—Bank 1", 1, "%"}},
        {"0179", {"Short term secondary oxygen sensor trim—Bank 2", 1, "%"}},
        {"017A", {"Long term secondary oxygen sensor trim—Bank 2", 1, "%"}},
        {"017B", {"Fuel rail pressure (absolute)", 2, "kPa"}},
        {"017C", {"Relative accelerator pedal position", 1, "%"}},
        {"017D", {"Hybrid battery pack remaining life", 1, "%"}},
        {"017E", {"Engine oil temperature", 1, "°C"}},
        {"017F", {"Fuel injection timing", 2, "°"}},
        {"0180", {"PIDs supported [81-A0]", 4, ""}},
        {"0181", {"Engine coolant temperature", 1, "°C"}},
        {"0182", {"Intake air temperature", 1, "°C"}},
        {"0183", {"Throttle position", 1, "%"}},
        {"0184", {"Fuel pressure", 1, "kPa"}},
        {"0185", {"Barometric pressure", 1, "kPa"}},
        {"0186", {"Commanded evaporative purge", 1, "%"}},
        {"0187", {"Fuel level input", 1, "%"}},
        {"0188", {"Ambient air temperature", 1, "°C"}},
        {"0189", {"Time run with MIL on", 2, "min"}},
        {"018A", {"Time since trouble codes cleared", 2, "min"}},
        {"018B", {"Maximum value for equivalence ratio", 2, ""}},
        {"018C", {"Maximum value for air flow rate", 2, "g/s"}},
        {"018D", {"Fuel Type", 1, ""}},
        {"018E", {"Ethanol fuel %", 1, "%"}},
        {"018F", {"Absolute Evap system vapor pressure", 2, "kPa"}},
        {"0190", {"PIDs supported [A1-C0]", 4, ""}},
        {"0191", {"Engine coolant temperature", 1, "°C"}},
        {"0192", {"Intake air temperature", 1, "°C"}},
        {"0193", {"Throttle position", 1, "%"}},
        {"0194", {"Fuel pressure", 1, "kPa"}},
        {"0195", {"Barometric pressure", 1, "kPa"}},
        {"0196", {"Commanded evaporative purge", 1, "%"}},
        {"0197", {"Fuel level input", 1, "%"}},
        {"0198", {"Ambient air temperature", 1, "°C"}},
        {"0199", {"Time run with MIL on", 2, "min"}},
        {"019A", {"Time since trouble codes cleared", 2, "min"}},
        {"019B", {"Maximum value for equivalence ratio", 2, ""}},
        {"019C", {"Maximum value for air flow rate", 2, "g/s"}},
        {"019D", {"Fuel Type", 1, ""}},
        {"019E", {"Ethanol fuel %", 1, "%"}},
        {"019F", {"Absolute Evap system vapor pressure", 2, "kPa"}},
        {"01A0", {"PIDs supported [C1-C8]", 4, ""}},
        {"01A1", {"Engine coolant temperature", 1, "°C"}},
        {"01A2", {"Intake air temperature", 1, "°C"}},
        {"01A3", {"Throttle position", 1, "%"}},
        {"01A4", {"Fuel pressure", 1, "kPa"}},
        {"01A5", {"Barometric pressure", 1, "kPa"}},
        {"01A6", {"Commanded evaporative purge", 1, "%"}},
        {"01A7", {"Fuel level input", 1, "%"}},
        {"01A8", {"Ambient air temperature", 1, "°C"}},
        {"01A9", {"Time run with MIL on", 2, "min"}},
        {"01AA", {"Time since trouble codes cleared", 2, "min"}},
        {"01AB", {"Maximum value for equivalence ratio", 2, ""}},
        {"01AC", {"Maximum value for air flow rate", 2, "g/s"}},
        {"01AD", {"Fuel Type", 1, ""}},
        {"01AE", {"Ethanol fuel %", 1, "%"}},
        {"01AF", {"Absolute Evap system vapor pressure", 2, "kPa"}},
        {"01B0", {"PIDs supported [C9-C8]", 4, ""}},
        {"01B1", {"Engine coolant temperature", 1, "°C"}},
        {"01B2", {"Intake air temperature", 1, "°C"}},
        {"01B3", {"Throttle position", 1, "%"}},
        {"01B4", {"Fuel pressure", 1, "kPa"}},
        {"01B5", {"Barometric pressure", 1, "kPa"}},
        {"01B6", {"Commanded evaporative purge", 1, "%"}},
        {"01B7", {"Fuel level input", 1, "%"}},
        {"01B8", {"Ambient air temperature", 1, "°C"}},
        {"01B9", {"Time run with MIL on", 2, "min"}},
        {"01BA", {"Time since trouble codes cleared", 2, "min"}},
        {"01BB", {"Maximum value for equivalence ratio", 2, ""}},
        {"01BC", {"Maximum value for air flow rate", 2, "g/s"}},
        {"01BD", {"Fuel Type", 1, ""}},
        {"01BE", {"Ethanol fuel %", 1, "%"}},
        {"01BF", {"Absolute Evap system vapor pressure", 2, "kPa"}},
        {"01C0", {"PIDs supported [C1-C8]", 4, ""}},
        {"01C1", {"Engine coolant temperature", 1, "°C"}},
        {"01C2", {"Intake air temperature", 1, "°C"}},
        {"01C3", {"Throttle position", 1, "%"}},
        {"01C4", {"Fuel pressure", 1, "kPa"}},
        {"01C5", {"Barometric pressure", 1, "kPa"}},
        {"01C6", {"Commanded evaporative purge", 1, "%"}},
        {"01C7", {"Fuel level input", 1, "%"}},
        {"01C8", {"Ambient air temperature", 1, "°C"}}
};


bool OBD2Communication::initialize() {
    // Initialize OBD-II communication (e.g., send AT commands)
    btConnection.send("AT Z\r"); // Reset all
    std::cout << "Initializing OBD2 communication" << std::endl;
    Sleep(1000); // Wait for device to reset

    btConnection.send("AT E0\r"); // Echo Off
    Sleep(100);
    btConnection.send("AT L0\r"); // Linefeeds Off
    Sleep(100);
    btConnection.send("AT SP 0\r"); // Set Protocol to Auto
    Sleep(100);
    btConnection.send("AT H1\r"); // Headers On
    Sleep(100);
    btConnection.send("AT DPN\r"); // Describe Protocol by Number
    Sleep(100);
    btConnection.send("0100\r"); // Check supported PIDs
    Sleep(100);

    std::string response = btConnection.receive();
    std::cout << "Initialization response: " << response << std::endl;

    return true;
}

void OBD2Communication::queryAllPIDs() {
    for (const auto& pid : pidDetails) {
        std::string command = pid.first + "\r";
        std::string response = sendCommand(command);
        parseAndPrintResponse(pid.first, response);
        Sleep(100); // Wait for a short while before sending the next command
    }
}

std::string OBD2Communication::sendCommand(const std::string& command) {
    btConnection.send(command);
    Sleep(100); // Wait for response
    return btConnection.receive();
}

int OBD2Communication::getSpeed() {
    std::string response = sendCommand("010D\r"); // PID for vehicle speed
//    std::cout << "Raw speed response: " << response << std::endl;
    return parseResponse(response, 1);
}

int OBD2Communication::getRPM() {
    std::string response = sendCommand("010C\r"); // PID for RPM
//    std::cout << "Raw RPM response: " << response << std::endl;
    return parseResponse(response, 2);
}

double OBD2Communication::getThrottlePosition() {
    std::string response = sendCommand("0111\r"); // PID for throttle position
//    std::cout << "Throttle Position: " << response << std::endl;
    return parseResponse(response, 1);
}

std::string OBD2Communication::getDTCs() {
    return sendCommand("03\r"); // Mode 03 for DTCs
}

void OBD2Communication::checkSupportedPIDs() {
    std::vector<std::string> commands = {"0100\r", "0120\r", "0140\r", "0160\r","0180\r", "0200\r", "0220\r", "0240\r", "0260\r", "0300\r", "0320\r", "0340\r", "0360\r", "0400\r", "0420\r", "0440\r", "0460\r", "0500\r", "0520\r", "0540\r", "0560\r", "0600\r", "0620\r", "0640\r", "0660\r", "0700\r", "0720\r", "0740\r", "0760\r", "0800\r", "0820\r", "0840\r", "0860\r", "0900\r", "0920\r", "0940\r", "0960\r", "0A00\r", "0A20\r", "0A40\r", "0A60\r", "0B00\r", "0B20\r", "0B40\r", "0B60\r"};
    for (const std::string& command : commands) {
        std::string response = sendCommand(command);
        if (response.empty()) {
            std::cout << "No response for command " << command << std::endl;
            continue;
        }
        std::cout << "Supported PIDs response for command " << command << ": " << response << std::endl;

        // Parse the response
        size_t start = response.find("41 ");
        if (start == std::string::npos) {
            std::cout << "Error parsing supported PIDs response. '41 ' not found in response. Trying to parse response as is." << std::endl;
            start = 0; // Try to parse the response as is
        } else {
            start += 3; // Skip "41 "
        }

        std::string data = response.substr(start);
        std::istringstream ss(data);

        std::string byteStr;
        int pidOffset = 0;

        if (command == "0120\r") {
            pidOffset = 32;
        } else if (command == "0140\r") {
            pidOffset = 64;
        } else if (command == "0160\r") {
            pidOffset = 96;
        }
        else if (command == "0180\r") {
            pidOffset = 128;
        }
        // Add more else if conditions here for other commands

        for (int i = 0; i < 4; ++i) { // Only read 4 bytes
            if (!(ss >> byteStr) || byteStr.length() != 2) {
                std::cout << "Error parsing supported PIDs response. Could not read byte " << i + 1 << " from response." << std::endl;
                break;
            }

            int value;
            std::istringstream(byteStr) >> std::hex >> value;

            for (int j = 0; j < 8; ++j) {
                if (value & (1 << (7 - j))) {
                    std::cout << "PID " << (pidOffset + i * 8 + j + 1) << " is supported" << std::endl;
                }
            }
        }
    }
}

double OBD2Communication::getBoostPressure() {
    std::string response = sendCommand("010B\r"); // PID for Intake Manifold Absolute Pressure
    std::cout << "Raw boost pressure response: " << response << std::endl;
    return parseResponse(response, 1);
}

double OBD2Communication::getBoostPressureActualValue() {
    std::string response = sendCommand("010B\r"); // PID for Boost Pressure Actual Value
//    std::cout << "Raw boost pressure actual value response: " << response << std::endl;
    return parseResponse(response, 1) * 10; // Convert kPa to mbar
}

double OBD2Communication::getBoostPressureSpecifiedValue() {
    std::string response = sendCommand("010C\r"); // PID for Boost Pressure Specified Value
//    std::cout << "Raw boost pressure specified value response: " << response << std::endl;
    return parseResponse(response, 1) * 10; // Convert kPa to mbar
}

void OBD2Communication::parseAndPrintResponse(const std::string& command, const std::string& response) {
    if (response.empty()) {
        std::cout << "No response for command " << command << std::endl;
        return;
    }

    std::cout << "Response for command " << command << ": " << response << std::endl;
    size_t start = response.find("41 ");
    if (start == std::string::npos) {
        std::cout << "Invalid response for command " << command << std::endl;
        return;
    }

    std::string data = response.substr(start + 3); // Skip "41 "
    std::istringstream ss(data);
    std::vector<int> bytes;
    std::string byteStr;

    while (ss >> byteStr) {
        int byteValue;
        std::istringstream(byteStr) >> std::hex >> byteValue;
        bytes.push_back(byteValue);
    }

    if (pidDetails.find(command) == pidDetails.end()) {
        std::cout << "Unknown PID length for command " << command << std::endl;
        return;
    }

    int length = pidDetails[command].length;
    if (bytes.size() < length) {
        std::cout << "Incomplete response for command " << command << std::endl;
        return;
    }

    // Print parsed values
    std::cout << pidDetails[command].description << ": ";
    if (command == "010C") { // RPM
        int rpm = ((bytes[2] * 256) + bytes[3]) / 4;
        std::cout << rpm << " " << pidDetails[command].unit << std::endl;
    } else if (command == "010D") { // Speed
        int speed = bytes[2];
        std::cout << speed << " " << pidDetails[command].unit << std::endl;
    } else if (command == "0105") { // Coolant temperature
        int temp = bytes[2] - 40;
        std::cout << temp << " " << pidDetails[command].unit << std::endl;
    } else {
        for (int i = 0; i < length; ++i) {
            std::cout << std::hex << bytes[i] << " ";
        }
        std::cout << pidDetails[command].unit << std::endl;
    }
}

int OBD2Communication::parseResponse(const std::string& response, int byteCount) {
    if (response.empty()) {
        return -1;
    }

    size_t start = response.find("41 ");
    if (start == std::string::npos) {
        return -1;
    }

    std::string data = response.substr(start + 6);
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

    return value;
}
