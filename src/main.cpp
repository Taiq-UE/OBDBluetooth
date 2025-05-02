#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <windows.h>
#include <locale>

#include <iostream>

#include "OpenAIDtcAnalyzer.hpp"

#ifdef USE_SIMULATED
#include "sim/SimBluetoothConnection.hpp"
#include "sim/SimOBD2Communication.hpp"
#else
#include "BluetoothConnection.hpp"
#include "OBD2Communication.hpp"
#endif

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "TEST" << std::flush;
//    Sleep(10000);
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
    engine.load(QUrl::fromLocalFile("C:/Users/kamil/CLionProjects/OBDBluetooth/src/ui/App.qml"));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    OpenAIDtcAnalyzer analyzer;
    QString dtcCodes = obd2.getDTCs(); // Przykładowe kody DTC

    // Konwersja QString na std::string
    std::string dtcCodesStd = dtcCodes.toStdString();
    std::cout << dtcCodesStd << std::endl;
    // Analiza kodów DTC
//    std::string analysisStd = analyzer.analyzeDtcCodes(dtcCodesStd);

    // Konwersja std::string na QString
//    QString analysis = QString::fromStdString(analysisStd);

    // Wyświetlenie wyniku
//    std::cout << "Analiza kodów DTC:\n" << analysis.toStdString() << std::endl;

    return app.exec();
}