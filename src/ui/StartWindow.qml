import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: startWindow
    title: qsTr("Start Window")

    // Layout dla głównych elementów
    Column {
        anchors.centerIn: parent
        spacing: 20

        Button {
            id: connectButton
            text: qsTr("Connect")
            onClicked: {
                connectButton.enabled = false  // Zablokowanie przycisku po kliknięciu

                // Po kliknięciu, próbujemy połączyć się z urządzeniem
                Qt.callLater(function () {
                    var btSuccess = btConnection.connect("COM5")
                    var obdSuccess = obd2.initialize()

                    if (btSuccess && obdSuccess) {
                        // Jeśli połączenie udane
                        connectionPopup.title = "Connection Successful"
                        connectionPopup.text = "Successfully connected to device."
                        connectionPopup.callback = function () {
                            connectButton.enabled = true
                            var component = Qt.createComponent("ConnectedWindow.qml")
                            if (component.status === Component.Ready) {
                                startWindow.parent.push(component)
                            } else {
                                console.log("Failed to load ConnectedWindow.qml:", component.errorString())
                            }
                        }
                        connectionPopup.open()
                    } else {
                        // Jeśli połączenie nieudane
                        connectionPopup.title = "Connection Failed"
                        connectionPopup.text = "Could not connect. Please try again."
                        connectionPopup.callback = function () {
                            connectButton.enabled = true
                        }
                        connectionPopup.open()
                    }
                })
            }
        }
    }

    // Popup do wyświetlania komunikatów
    Popup {
        id: connectionPopup
        modal: true
        focus: true
        anchors.centerIn: parent
        width: 300
        height: 150

        background: Rectangle {
            color: "#ffffff"
            radius: 8
            border.color: "#888"
        }

        Column {
            anchors.centerIn: parent
            spacing: 10

            Label {
                id: popupLabel
                text: connectionPopup.text
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                text: "OK"
                onClicked: {
                    connectionPopup.close()
                    if (connectionPopup.callback !== null) {
                        connectionPopup.callback()
                    }
                }
            }
        }

        property string text: ""
        property string title: ""
        property var callback: null
    }
}
