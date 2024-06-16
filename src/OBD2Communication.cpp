#include "OBD2Communication.h"
#include <iostream>
#include <sstream>
#include <vector>

OBD2Communication::OBD2Communication(BluetoothConnection& bt) : btConnection(bt) {}

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
    std::string response = sendCommand("0685\r"); // PID for throttle position
    std::cout << "Boost: " << response << std::endl;
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

std::string OBD2Communication::sendCommand(const std::string& command) {
    btConnection.send(command);
    Sleep(100); // Wait for response
    return btConnection.receive();
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
