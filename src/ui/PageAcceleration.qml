import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Page {
    id: pageAcceleration
    title: qsTr("Acceleration Test")

    property int startSpeed: 0
    property int targetSpeed: 0
    property double elapsedTime: 0.0
    property int currentSpeed: 0
    property double startTime: 0

    // ListModel do przechowywania wyników
    ListModel {
        id: resultsModel
    }

    function checkSpeed() {
        currentSpeed = obd2.getSpeed(); // Odczytaj prędkość z backendu
        elapsedTime = startTime > 0 ? (Date.now() - startTime) / 1000.0 : 0.0; // Oblicz czas

        if (currentSpeed > startSpeed) {
            if (startTime === 0) {
                startTime = Date.now(); // Rozpocznij pomiar czasu
            }

            if (currentSpeed >= targetSpeed) {
                var endTime = Date.now();
                var totalElapsedTime = (endTime - startTime) / 1000.0; // Czas w sekundach

                // Dodaj wynik do ListModel
                resultsModel.append({
                    startToTarget: startSpeed + " -> " + targetSpeed,
                    time: totalElapsedTime.toFixed(2) + " s"
                });

                speedCheckTimer.stop(); // Zatrzymaj sprawdzanie prędkości
                startTime = 0; // Resetuj czas początkowy
                elapsedTime = 0; // Resetuj czas
                currentSpeed = 0; // Resetuj prędkość
                obd2.setSpeed(0); // Zresetuj prędkość w backendzie
                console.log("Test completed in " + totalElapsedTime + " seconds");
            }
        }
    }

    Timer {
        id: speedCheckTimer
        interval: 10 // Co 100 ms sprawdzamy prędkość
        repeat: true
        onTriggered: checkSpeed()
    }

    Item {
        anchors.fill: parent

        Column {
            anchors.fill: parent
            spacing: 20

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                TextField {
                    id: startSpeedInput
                    placeholderText: qsTr("Start Speed")
                    inputMethodHints: Qt.ImhDigitsOnly
                    width: 100
                }

                TextField {
                    id: targetSpeedInput
                    placeholderText: qsTr("Target Speed")
                    inputMethodHints: Qt.ImhDigitsOnly
                    width: 100
                }

                Button {
                    text: qsTr("Start Test")
                    onClicked: {
                        startSpeed = parseInt(startSpeedInput.text)
                        targetSpeed = parseInt(targetSpeedInput.text)

                        if (isNaN(startSpeed) || isNaN(targetSpeed) || startSpeed >= targetSpeed) {
                            console.log("Invalid input: Start speed must be less than target speed.");
                            return;
                        }

                        startTest();
                    }
                }
            }

            // Sekcja do wyświetlania bieżącej prędkości i czasu
            Rectangle {
                width: parent.width - 40
                height: 80
                color: "#f0f0f0"
                radius: 5
                border.color: "#ccc"
                anchors.horizontalCenter: parent.horizontalCenter

                Row {
                    anchors.centerIn: parent
                    spacing: 20

                    Column {
                        spacing: 5
                        Text {
                            text: qsTr("Current Speed:")
                            font.bold: true
                        }
                        Text {
                            id: speedDisplay
                            text: currentSpeed + " km/h"
                            font.pointSize: 16
                            color: "#333"
                        }
                    }

                    Column {
                        spacing: 5
                        Text {
                            text: qsTr("Elapsed Time:")
                            font.bold: true
                        }
                        Text {
                            id: timeDisplay
                            text: elapsedTime.toFixed(2) + " s"
                            font.pointSize: 16
                            color: "#333"
                        }
                    }
                }
            }

            // Tabela wyników
            Rectangle {
                width: parent.width - 40
                height: 300
                color: "#ffffff"
                border.color: "#ccc"
                radius: 5
                anchors.horizontalCenter: parent.horizontalCenter

                Column {
                    anchors.fill: parent
                    spacing: 5
                    padding: 10

                    Text {
                        text: qsTr("Results")
                        font.bold: true
                        font.pointSize: 14
                        color: "#333"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    ListView {
                        id: resultsList
                        anchors.fill: parent
                        model: resultsModel
                        clip: true

                        delegate: Row {
                            width: parent.width
                            height: 40
                            spacing: 10
                            Rectangle {
                                width: parent.width * 0.6
                                height: parent.height
                                color: "#f9f9f9"
                                border.color: "#ccc"
                                Text {
                                    anchors.centerIn: parent
                                    text: model.startToTarget
                                }
                            }
                            Rectangle {
                                width: parent.width * 0.4
                                height: parent.height
                                color: "#f9f9f9"
                                border.color: "#ccc"
                                Text {
                                    anchors.centerIn: parent
                                    text: model.time
                                }
                            }
                        }
                    }
                }
            }
        }

        Button {
            text: qsTr("Back")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: {
                startTime = 0; // Resetuj czas początkowy
                elapsedTime = 0; // Resetuj czas
                currentSpeed = 0; // Resetuj prędkość
                obd2.setSpeed(0); // Zresetuj prędkość w backendzie
                var stackView = pageAcceleration.parent
                stackView.pop();
            }
        }
    }

    function startTest() {
        console.log("Starting acceleration test from " + startSpeed + " to " + targetSpeed);
        startTime = 0; // Resetuj czas początkowy
        elapsedTime = 0; // Resetuj czas wyświetlany
        currentSpeed = 0; // Resetuj bieżącą prędkość
        speedCheckTimer.start(); // Rozpocznij sprawdzanie prędkości
    }
}
