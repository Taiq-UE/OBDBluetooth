#pragma once
#include <string>
#include <windows.h>

class BluetoothConnection {
public:
    BluetoothConnection();
    ~BluetoothConnection();
    bool connect(const std::string& port);
    bool send(const std::string& data);
    std::string receive();
private:
    HANDLE hSerial;
};
