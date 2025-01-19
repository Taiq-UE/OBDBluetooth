#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#ifdef USE_SIMULATED
#include "sim/SimBluetoothConnection.hpp"
#include "sim/SimOBD2Communication.hpp"
#else
#include "BluetoothConnection.hpp"
#include "OBD2Communication.hpp"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

#ifdef USE_SIMULATED
    SimBluetoothConnection btConnection;
    SimOBD2Communication obd2(btConnection);
#else
    BluetoothConnection btConnection;
    OBD2Communication obd2(btConnection);
#endif

    engine.rootContext()->setContextProperty("btConnection", &btConnection);
    engine.rootContext()->setContextProperty("obd2", &obd2);
    engine.load(QUrl::fromLocalFile("D:/REPO/OBDBluetooth/src/ui/App.qml"));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}