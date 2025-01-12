import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: rectangle
    width: 1920
    height: 1080
    color: "#858585"

    Loader {
        id: connectingWindowLoader
    }

    Button {
        id: connectButton
        x: 879
        y: 498
        width: 163
        height: 84
        text: qsTr("Connect")
        onClicked: {
            connectButton.visible = false
            connectingWindowLoader.source = "ConnectingWindow.qml"
            Qt.callLater(function() {
                var success = btConnection.connect("COM5")
                connectingWindowLoader.source = ""
                if (success) {
                    Qt.createComponent("ConnectedWindow.qml").createObject(rectangle)
                } else {
                    connectButton.visible = true
                    console.log("Connection failed")
                }
            })
        }
    }
}