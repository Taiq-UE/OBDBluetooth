#include "OBD2CommunicationSimulator.h"

OBD2CommunicationSimulator::OBD2CommunicationSimulator(BluetoothConnection& bt) : OBD2Communication(bt), generator(std::random_device{}()), distribution(0, 255) {}

bool OBD2CommunicationSimulator::initialize() {
    // Zawsze udajemy, że inicjalizacja jest udana
    return true;
}

int OBD2CommunicationSimulator::getSpeed() {
    // Zwracamy losową prędkość
    return distribution(generator);
}

int OBD2CommunicationSimulator::getRPM() {
    // Zwracamy losowe obroty na minutę
    return distribution(generator);
}

std::string OBD2CommunicationSimulator::getDTCs() {
    // Zwracamy losowe kody błędów diagnostycznych
    char buffer[5];
    for (int i = 0; i < sizeof(buffer) - 1; ++i) {
        buffer[i] = static_cast<char>(distribution(generator) % 26 + 'A');
    }
    buffer[sizeof(buffer) - 1] = '\0';
    return std::string(buffer);
}