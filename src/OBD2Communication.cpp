#include "OBD2Communication.h"
#include <iostream>
#include <sstream>

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
    std::cout << "Raw speed response: " << response << std::endl;
    return parseResponse(response, 1);
}

int OBD2Communication::getRPM() {
    std::string response = sendCommand("010C\r"); // PID for RPM
    std::cout << "Raw RPM response: " << response << std::endl;
    return parseResponse(response, 2);
}

std::string OBD2Communication::getDTCs() {
    return sendCommand("03\r"); // Mode 03 for DTCs
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

    // Find the start of the actual data
    size_t start = response.find("41 ");
    if (start == std::string::npos) {
        return -1;
    }

    std::string data = response.substr(start + 3); // Skip "41 "
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
        value = value / 4; // RPM needs to be divided by 4 as per OBD-II spec
    }

    return value;
}
