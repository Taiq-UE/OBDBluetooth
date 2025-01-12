import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 1920
    height: 1080
    color: "#858585"

    Button {
        id: readErrorsButton
        x: 597
        y: 853
        width: 192
        height: 97
        text: qsTr("Read Errors with AI Assistant")
    }

    Button {
        id: accelerationButton
        x: 864
        y: 853
        width: 192
        height: 97
        text: "Acceleration"
    }

    Button {
        id: chartButton
        x: 1129
        y: 853
        width: 192
        height: 97
        text: qsTr("Turbo pressure / Boost chart")
    }

    Button {
        id: disconnectButton
        x: 1397
        y: 853
        width: 192
        height: 97
        text: qsTr("Disconnect")
    }

    Button {
        id: dashboardButton
        x: 333
        y: 853
        width: 192
        height: 97
        text: "Dashboard"
    }
}
