#ifndef IBLUETOOTHCONNECTION_HPP
#define IBLUETOOTHCONNECTION_HPP

#include <QString>

class IBluetoothConnection {
public:
    virtual ~IBluetoothConnection() = default;
    virtual bool connect(const QString& port) = 0;
    virtual bool disconnect() = 0;
    virtual bool send(const QString& data) = 0;
    virtual QString receive() = 0;
};

#endif // IBLUETOOTHCONNECTION_HPP