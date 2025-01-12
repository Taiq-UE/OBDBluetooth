// #pragma once
// #include "BluetoothConnection.hpp"
// #include <random>
//
// class BluetoothConnectionSimulator : public BluetoothConnection {
// public:
//     BluetoothConnectionSimulator();
//     bool connect(const std::string& port) override;
//     bool send(const std::string& data) override;
//     std::string receive() override;
//
// private:
//     std::mt19937 generator;
//     std::uniform_int_distribution<int> distribution;
// };