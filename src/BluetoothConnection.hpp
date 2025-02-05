#ifndef BLUETOOTHCONNECTION_HPP
#define BLUETOOTHCONNECTION_HPP

#include <QObject>
#include <QString>
#include <windows.h>

#include "src/interface/IBluetoothConnection.hpp"

class BluetoothConnection : public QObject, public IBluetoothConnection {
    Q_OBJECT
public:
    BluetoothConnection();
    ~BluetoothConnection() override;

    Q_INVOKABLE bool connect(const QString& port) override;
    Q_INVOKABLE bool disconnect() override;
    Q_INVOKABLE bool send(const QString& data) override;
    Q_INVOKABLE QString receive() override;

private:
    HANDLE hSerial;
};

#endif // BLUETOOTHCONNECTION_HPP