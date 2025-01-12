import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: rectangle
    width: 1920
    height: 1080
    color: "#858585"

    Button {
        id: connectButton
        x: 879
        y: 498
        width: 163
        height: 84
        text: qsTr("Connect")
        onClicked: {
            if (btConnection.connect("COM5")) {
                Qt.createComponent("ConnectedWindow.qml").createObject(rectangle)
            } else {
                console.log("Connection failed")
            }
        }
    }
}