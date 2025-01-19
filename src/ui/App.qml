import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    visible: true
    width: 1080
    height: 720
    title: qsTr("OBD Bluetooth App")

    // Główny kontener do nawigacji
    StackView {
        id: stackView
        anchors.fill: parent

        // Ustawiamy pierwszą stronę:
        initialItem: Qt.createComponent("StartWindow.qml")
    }
}
