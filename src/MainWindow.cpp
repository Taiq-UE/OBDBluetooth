#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "BluetoothConnection.h"
#include "OBD2Communication.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
//    BluetoothConnection bt2;
//    if (!bt2.connect("COM5")) {
//        QMessageBox::critical(this, "Error", "Failed to connect to OBD2 device");
//        return;
//    }
//
//    OBD2Communication obd2(bt2);
//    if (!obd2.initialize()) {
//        QMessageBox::critical(this, "Error", "Failed to initialize OBD2 communication");
//        return;
//    }

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *dashboardButton = new QPushButton("Dashboard", centralWidget);
    QPushButton *readErrorsButton = new QPushButton("Read Errors", centralWidget);
    QPushButton *measureAccelerationButton = new QPushButton("Measure Acceleration", centralWidget);
    QPushButton *showBoostRpmChartButton = new QPushButton("Show Boost/RPM Chart", centralWidget);

    layout->addWidget(dashboardButton);
    layout->addWidget(readErrorsButton);
    layout->addWidget(measureAccelerationButton);
    layout->addWidget(showBoostRpmChartButton);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    resize(800, 600);
    centralWidget->setStyleSheet("background-color: #808080;");
    QString modernButtonStyle = "QPushButton {"
                                "    background-color: #4CAF50;"
                                "    border: none;"
                                "    color: white;"
                                "    padding: 15px 32px;"
                                "    text-align: center;"
                                "    text-decoration: none;"
                                "    font-size: 16px;"
                                "    margin: 4px 2px;"
                                "    border-radius: 12px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: white; "
                                "    color: black; "
                                "}";

    dashboardButton->setStyleSheet(modernButtonStyle);
    readErrorsButton->setStyleSheet(modernButtonStyle);
    measureAccelerationButton->setStyleSheet(modernButtonStyle);
    showBoostRpmChartButton->setStyleSheet(modernButtonStyle);
}

MainWindow::~MainWindow() = default;