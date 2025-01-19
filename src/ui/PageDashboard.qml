import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: pageDashboard
    title: qsTr("Dashboard")

    Item {
        anchors.fill: parent

        Button {
            text: qsTr("Back")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: {
                var stackView = pageDashboard.parent; // Odwołanie do StackView
                stackView.pop(); // Powrót do poprzedniej strony
            }
        }
    }
}
