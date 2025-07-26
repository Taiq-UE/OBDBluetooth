import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: pageReadErrors
    title: qsTr("Read Errors")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Button {
            text: "Read Errors"
            onClicked: {
                errorOutput.text = obd2.getDTCs();
            }
        }

        TextArea {
            id: errorOutput
            readOnly: true
            wrapMode: Text.Wrap
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            placeholderText: "Detected DTC codes will appear here..."
        }

        Button {
            text: "Analyze Errors"
            onClicked: {
                var analysis = analyzer.analyzeDtcCodes(errorOutput.text);
                analysisOutput.text = analysis;
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: analysisOutput
                readOnly: true
                wrapMode: Text.Wrap
                placeholderText: "AI-based analysis will appear here..."
            }
        }

        Button {
            text: qsTr("Back")
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                var stackView = pageReadErrors.parent;
                stackView.pop();
            }
        }
    }
}