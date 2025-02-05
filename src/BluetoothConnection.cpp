#include <iostream>
#include <stdexcept>

#include "BluetoothConnection.hpp"

BluetoothConnection::BluetoothConnection() : hSerial(INVALID_HANDLE_VALUE) {}

BluetoothConnection::~BluetoothConnection() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
    }
}

bool BluetoothConnection::connect(const QString& port) {
    std::wstring wport = port.toStdWString();
    hSerial = CreateFile(wport.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port" << std::endl;
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

bool BluetoothConnection::disconnect() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        return true;
    }
    return false;
}

bool BluetoothConnection::send(const QString& data) {
    DWORD bytesWritten;
    QByteArray byteArray = data.toUtf8();
    if (!WriteFile(hSerial, byteArray.constData(), byteArray.size(), &bytesWritten, NULL)) {
        std::cerr << "Error writing to serial port" << std::endl;
        return false;
    }
    return true;
}

QString BluetoothConnection::receive() {
    char buffer[1024];
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
        std::cerr << "Error reading from serial port" << std::endl;
        return "";
    }
    return QString::fromUtf8(buffer, bytesRead);
}
