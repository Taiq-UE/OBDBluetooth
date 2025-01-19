#include <iostream>
#include <windows.h>
#include <QThread>

#include "SimBluetoothConnection.hpp"

bool SimBluetoothConnection::connect(const QString& port) {
    QThread::sleep(2); // Symuluje czasochłonne połączenie
    std::cout << "Simulated connect to port: " << port.toStdString() << std::endl;
    return true; // Zawsze zwraca sukces
}

void SimBluetoothConnection::connectAsync(const QString& port) {
    QTimer::singleShot(500, [this, port]() {
        QThread::sleep(2); // Symulacja czasochłonnego połączenia
        std::cout << "Simulated connect to port: " << port.toStdString() << std::endl;

        bool success = true; // Symulacja sukcesu
        emit connectionFinished(success ? "Connected" : "Connection Failed");
    });
}

bool SimBluetoothConnection::disconnect() {
    std::cout << "Simulated disconnect" << std::endl;
    emit connectionFinished("Disconnected"); // Emitujemy status rozłączenia
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