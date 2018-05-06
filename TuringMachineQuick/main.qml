import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Turing Machine Simulator")
    signal openFileRequest(var url)

    FileDialog {
        id: openDialog
        onAccepted: openFileRequest(fileUrl)
    }

    menuBar: MenuBar {
           Menu {
               title: qsTr("&File")
               Action { text: qsTr("&Open..."); onTriggered: openDialog.open() }
               Action { text: qsTr("&Save") }
               Action { text: qsTr("Save &As...") }
           }
           Menu {
               title: qsTr("&Run")
               Action { text: qsTr("Compile") }
               MenuSeparator { id: menuSeparator }
               Action { text: qsTr("Single step") }
               Action { text: qsTr("Auto step") }
           }
       }

    ScrollView {
        id: scrollView
        height: 35
        font.pointSize: 14
        anchors.right: parent.right
        anchors.rightMargin: 49
        anchors.left: parent.left
        anchors.leftMargin: 49
        anchors.top: parent.top
        anchors.topMargin: 18
        clip: true

        ListView {
            id: tapeView
            x: 11
            y: 34
            width: 357
            height: 35
            orientation: ListView.Horizontal
            model: tapeModel
            delegate: TextField  {
                x: 5
                width: 35
                height: 35
                Row {
                    id: row1
                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    TextEdit {
        id: textEdit
        objectName: "textEdit"
        x: 38
        y: 214
        width: 162
        height: 152
        text: qsTr("Text Edit")
//        anchors.right: menuSeparator.right
        //anchors.horizontalCenterOffset: 89
        font.pixelSize: 12
        //anchors.horizontalCenter: menuSeparator.horizontalCenter
    }


}
