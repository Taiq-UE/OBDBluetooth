import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: connectedWindow
    title: qsTr("Page 2")

    Item {
        anchors.fill: parent

        Row {
            id: buttonsRow
            anchors.centerIn: parent
            spacing: 10

            Button {
                text: qsTr("Read Errors")
                onClicked: {
                    var stackView = connectedWindow.parent;
                    stackView.push(Qt.createComponent("PageReadErrors.qml"));
                }
            }

            Button {
                text: qsTr("Acceleration Test")
                onClicked: {
                    var stackView = connectedWindow.parent;
                    stackView.push(Qt.createComponent("PageAcceleration.qml"));
                }
            }

            // Button {
            //     text: qsTr("Turbo pressure/Boost chart")
            //     onClicked: {
            //         var stackView = connectedWindow.parent;
            //         stackView.push(Qt.createComponent("PageTurboChart.qml"));
            //     }
            // }

            // Button {
            //     text: qsTr("Dashboard")
            //     onClicked: {
            //         var stackView = connectedWindow.parent;
            //         stackView.push(Qt.createComponent("PageDashboard.qml"));
            //     }
            // }

            Button {
                text: qsTr("Disconnect")
                onClicked: {
                    btConnection.disconnect(); // Wywołanie disconnect
                    var stackView = connectedWindow.parent;
                    stackView.pop(); // Powrót do poprzedniego okna
                }
            }
        }
    }

    // Obsługa zmiany statusu
    // Connections {
    //     target: btConnection
    //     onConnectionFinished: function(newStatus) {
    //         statusText.text = qsTr("Status: ") + newStatus;
    //     }
    // }
}
