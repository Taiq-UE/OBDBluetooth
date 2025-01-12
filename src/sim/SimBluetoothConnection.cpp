#include <iostream>

#include "SimBluetoothConnection.hpp"

bool SimBluetoothConnection::connect(const QString& port) {
    std::cout << "Simulated connect to port: " << port.toStdString() << std::endl;
    return true;
}

bool SimBluetoothConnection::disconnect() {
    std::cout << "Simulated disconnect" << std::endl;
    return true;
}

bool SimBluetoothConnection::send(const QString& data) {
    std::cout << "Simulated send data: " << data.toStdString() << std::endl;
    return true;
}

QString SimBluetoothConnection::receive() {
    std::cout << "Simulated receive data" << std::endl;
    return "Simulated data";
}