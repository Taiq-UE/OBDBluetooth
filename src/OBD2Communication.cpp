#include "OBD2Communication.h"
#include <iostream>
#include <sstream>

OBD2Communication::OBD2Communication(BluetoothConnection& bt) : btConnection(bt) {}

bool OBD2Communication::initialize() {
    // Initialize OBD-II communication (e.g., send AT commands)
    btConnection.send("AT Z\r"); // Reset all
    std::cout << "Initializing OBD2 communication" << std::endl;
    Sleep(1000); // Wait for device to reset
    return true;
}

int OBD2Communication::getSpeed() {
    std::string response = sendCommand("01 0D\r"); // PID for vehicle speed
    return parseResponse(response);
}

int OBD2Communication::getRPM() {
    std::string response = sendCommand("01 0C\r"); // PID for RPM
    return parseResponse(response);
}

std::string OBD2Communication::getDTCs() {
    return sendCommand("03\r"); // Mode 03 for DTCs
}

std::string OBD2Communication::sendCommand(const std::string& command) {
    btConnection.send(command);
    Sleep(100); // Wait for response
    return btConnection.receive();
}

int OBD2Communication::parseResponse(const std::string& response) {
    // Parse the hexadecimal response to an integer
    if (response.empty()) {
        return -1;
    }
    std::istringstream ss(response.substr(4)); // Skip the header
    int value;
    ss >> std::hex >> value;
    return value;
}
