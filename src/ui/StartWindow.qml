import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: startWindow
    title: qsTr("Start Window")

    Item {
        anchors.fill: parent

        Column {
            id: header
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            spacing: 10

            Text {
                id: statusText
                text: qsTr("Status: Disconnected") // Początkowy status
                font.pointSize: 18
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Column {
            anchors.centerIn: parent
            spacing: 20

            Button {
                id: connectButton
                text: qsTr("Connect")
                onClicked: {
                    connectButton.visible = false
                    busyIndicator.visible = true

                    btConnection.connectAsync("COM5")
                    obd2.initialize()
                }
            }

            BusyIndicator {
                id: busyIndicator
                visible: false
                running: true
            }
        }
    }

    // Obsługa zmiany statusu
    Connections {
        target: btConnection
        onConnectionFinished: function(newStatus) {
            statusText.text = qsTr("Status: ") + newStatus;

            // Jeśli połączenie zakończone sukcesem, przechodzimy do ConnectedWindow
            if (newStatus === "Connected") {
                console.log("Connected successfully!");
                busyIndicator.visible = false;
                connectButton.visible = true;

                var stackView = startWindow.parent;
                stackView.push(Qt.createComponent("ConnectedWindow.qml"));
            } else {
                console.log("Connection failed or disconnected.");
                busyIndicator.visible = false;
                connectButton.visible = true;
            }
        }
    }
}
