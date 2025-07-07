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
    SimBluetoothConnection bt2;
    SimOBD2Communication obd2(bt2);
#else
    BluetoothConnection bt2;
    if (!bt2.connect("COM5")) {
        std::cerr << "Failed to connect to OBD2 device" << std::endl;
    } else {
        std::cout << "Connection to OBD2 device successful" << std::endl;
    }

    OBD2Communication obd2(bt2);
    if (!obd2.initialize()) {
        std::cerr << "Failed to initialize OBD2 communication" << std::endl;
    } else {
        std::cout << "OBD2 communication initialized" << std::endl;
    }
#endif

    OpenAIDtcAnalyzer analyzer;
    QString dtcCodes = obd2.getDTCs(); // Przykładowe kody DTC

    // Konwersja QString na std::string
    std::string dtcCodesStd = dtcCodes.toStdString();
//    std::cout << " DTC: " << dtcCodesStd << std::endl;

    dtcCodes = obd2.getDTCs();
    dtcCodesStd = dtcCodes.toStdString();
    std::cout << dtcCodesStd << std::endl;



//    int coolant = obd2.getRPM();
//    std::cout << "RPM: " << coolant << std::endl;

    engine.rootContext()->setContextProperty("btConnection", &bt2);
    engine.rootContext()->setContextProperty("obd2", &obd2);
    engine.load(QUrl::fromLocalFile("C:/Users/kamil/CLionProjects/OBDBluetooth/src/ui/App.qml"));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    std::cout << "DTC Codes: " << dtcCodesStd << std::endl;
//     Analiza kodów DTC
    std::string analysisStd = analyzer.analyzeDtcCodes(dtcCodesStd);

//     Konwersja std::string na QString*
    QString analysis = QString::fromStdString(analysisStd);

//     Wyświetlenie wyniku
    std::cout << "Analiza kodów DTC:\n" << analysis.toStdString() << std::endl;

    return app.exec();
}