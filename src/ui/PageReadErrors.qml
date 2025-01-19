import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: pageReadErrors
    title: qsTr("Read Errors")

    Item {
        anchors.fill: parent

        Button {
            text: qsTr("Back")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: {
                var stackView = pageReadErrors.parent; // Odwołanie do StackView
                stackView.pop(); // Powrót do poprzedniej strony
            }
        }
    }
}
