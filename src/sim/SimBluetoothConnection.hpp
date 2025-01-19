#ifndef SIMBLUETOOTHCONNECTION_HPP
#define SIMBLUETOOTHCONNECTION_HPP

#include <QObject>
#include <QString>
#include <QTimer>
#include <iostream>
#include "src/interface/IBluetoothConnection.hpp"

class SimBluetoothConnection : public QObject, public IBluetoothConnection {
    Q_OBJECT
public:
    explicit SimBluetoothConnection(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE bool connect(const QString& port) override;   // Szybka synchronizacja
    Q_INVOKABLE void connectAsync(const QString& port);       // Asynchroniczna wersja
    Q_INVOKABLE bool disconnect() override;
    Q_INVOKABLE bool send(const QString& data) override;
    Q_INVOKABLE QString receive() override;

    signals:
        void connectionFinished(const QString& status);
};

#endif // SIMBLUETOOTHCONNECTION_HPP
