#ifndef SIMBLUETOOTHCONNECTION_HPP
#define SIMBLUETOOTHCONNECTION_HPP

#include <QObject>
#include <QString>

#include "src/interface/IBluetoothConnection.hpp"

class SimBluetoothConnection : public QObject, public IBluetoothConnection {
    Q_OBJECT
public:
    Q_INVOKABLE bool connect(const QString& port) override;
    Q_INVOKABLE bool disconnect() override;
    Q_INVOKABLE bool send(const QString& data) override;
    Q_INVOKABLE QString receive() override;
};

#endif // SIMBLUETOOTHCONNECTION_HPP