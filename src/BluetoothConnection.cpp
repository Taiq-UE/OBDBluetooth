#include "BluetoothConnection.h"
#include <iostream>
#include <stdexcept>

BluetoothConnection::BluetoothConnection() : hSerial(INVALID_HANDLE_VALUE) {}

BluetoothConnection::~BluetoothConnection() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
    }
}

bool BluetoothConnection::connect(const std::string& port) {
    hSerial = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cout << "Error opening serial port" << std::endl;
        return false;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state" << std::endl;
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port state" << std::endl;
        return false;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error setting serial port timeouts" << std::endl;
        return false;
    }

    return true;
}

bool BluetoothConnection::send(const std::string& data) {
    DWORD bytesWritten;
    Sleep(400);
    if (!WriteFile(hSerial, data.c_str(), data.size(), &bytesWritten, NULL)) {
        std::cerr << "Error writing to serial port" << std::endl;
        return false;
    }
    return true;
}

std::string BluetoothConnection::receive() {
    char buffer[1024];
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
        std::cerr << "Error reading from serial port" << std::endl;
        return "";
    }
    return std::string(buffer, bytesRead);
}
