#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#ifdef USE_SIMULATED
#include "sim/SimBluetoothConnection.hpp"
#else
#include "BluetoothConnection.hpp"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

#ifdef USE_SIMULATED
    SimBluetoothConnection btConnection;
#else
    BluetoothConnection btConnection;
#endif

    engine.rootContext()->setContextProperty("btConnection", &btConnection);

    engine.load(QUrl::fromLocalFile("D:/REPO/OBDBluetooth/src/ui/App.qml"));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}