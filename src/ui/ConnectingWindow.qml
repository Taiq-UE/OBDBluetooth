import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 1920
    height: 1080
    color: "#858585"

    BusyIndicator {
        id: busyIndicator
        x: 810
        y: 401
        width: 301
        height: 187
    }

    Text {
        id: _text
        x: 657
        y: 609
        width: 608
        height: 145
        text: qsTr("Connecting...")
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
    }
}
