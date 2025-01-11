#include "BluetoothConnectionSimulator.hpp"

BluetoothConnectionSimulator::BluetoothConnectionSimulator() : BluetoothConnection(), generator(std::random_device{}()), distribution(0, 255) {}

bool BluetoothConnectionSimulator::connect(const std::string& port) {
    // Zawsze udajemy, że połączenie jest udane
    return true;
}

bool BluetoothConnectionSimulator::send(const std::string& data) {
    // Zawsze udajemy, że wysyłanie danych jest udane
    return true;
}

std::string BluetoothConnectionSimulator::receive() {
    // Zwracamy losowe dane
    char buffer[1024];
    for (int i = 0; i < sizeof(buffer) - 1; ++i) {
        buffer[i] = static_cast<char>(distribution(generator));
    }
    buffer[sizeof(buffer) - 1] = '\0';
    return std::string(buffer);
}