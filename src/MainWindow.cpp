#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "BluetoothConnection.h"
#include "OBD2Communication.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

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
                                "    background-color: #318C49; "
                                "    color: white; "
                                "}";

    QPushButton *connectButton = new QPushButton("Connect", centralWidget);
    connectButton->setStyleSheet(modernButtonStyle);
    layout->addWidget(connectButton);

    QPushButton *disconnectButton = new QPushButton("Disconnect", this);
    disconnectButton->setStyleSheet(modernButtonStyle);
    disconnectButton->hide();
    layout->addWidget(disconnectButton);

    connect(connectButton, &QPushButton::clicked, [this, connectButton, disconnectButton, layout, modernButtonStyle]() {
//        BluetoothConnection bt2;
//        if (!bt2.connect("COM5")) {
//            QMessageBox::critical(this, "Error", "Failed to connect to OBD2 device");
//            return;
//        }
//
//        OBD2Communication obd2(bt2);
//        if (!obd2.initialize()) {
//            QMessageBox::critical(this, "Error", "Failed to initialize OBD2 communication");
//            return;
//        }

        connectButton->hide();
        disconnectButton->show();

        QPushButton *dashboardButton = new QPushButton("Dashboard", this);
        QPushButton *readErrorsButton = new QPushButton("Read Errors", this);
        QPushButton *measureAccelerationButton = new QPushButton("Measure Acceleration", this);
        QPushButton *showBoostRpmChartButton = new QPushButton("Show Boost/RPM Chart", this);

        dashboardButton->setStyleSheet(modernButtonStyle);
        readErrorsButton->setStyleSheet(modernButtonStyle);
        measureAccelerationButton->setStyleSheet(modernButtonStyle);
        showBoostRpmChartButton->setStyleSheet(modernButtonStyle);

        layout->addWidget(dashboardButton);
        layout->addWidget(readErrorsButton);
        layout->addWidget(measureAccelerationButton);
        layout->addWidget(showBoostRpmChartButton);
    });

    connect(disconnectButton, &QPushButton::clicked, [this, connectButton, disconnectButton, layout]() {
//        bt2.disconnect();

        disconnectButton->hide();
        connectButton->show();

        QLayoutItem *item;
        while ((item = layout->takeAt(2)) != nullptr) {
            delete item->widget();
            delete item;
        }
    });

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    resize(800, 600);
    centralWidget->setStyleSheet("background-color: #808080;");
}

MainWindow::~MainWindow() = default;