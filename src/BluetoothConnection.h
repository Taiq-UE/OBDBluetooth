#pragma once
#include <string>
#include <windows.h>

class BluetoothConnection {
public:
    BluetoothConnection();
    virtual ~BluetoothConnection();

    virtual bool connect(const std::string& port);
    bool disconnect();
    virtual bool send(const std::string& data);
    virtual std::string receive();

private:
    HANDLE hSerial;
};
