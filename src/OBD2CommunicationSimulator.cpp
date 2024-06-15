#include "OBD2CommunicationSimulator.h"

#include <iomanip> // for std::setw and std::setfill

OBD2CommunicationSimulator::OBD2CommunicationSimulator(BluetoothConnection& bt) : OBD2Communication(bt), generator(std::random_device{}()), distribution(0, 1918) {}

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
    // Zwracamy kilka losowych kodów błędów diagnostycznych
    std::string dtcs;
    for (int i = 0; i < 5; ++i) { // Generate 5 random DTCs
        int number = distribution(generator) % 1919; // Generate a number between 0 and 1918
        std::ostringstream oss;
        oss << "P" << std::setw(4) << std::setfill('0') << number; // Convert the number to a string, padding with zeros if necessary
        dtcs += oss.str() + " ";
    }
    return dtcs;
}