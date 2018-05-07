import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.1

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Turing Machine Simulator")
    signal openFileRequest(var url)
    signal compileAction()
    signal singleStepAction()
    signal autoStepAction()

    function showDialog(msg) {
        stepTimer.running = false
        messageDialog.text = msg
        messageDialog.visible = true
    }

    FileDialog {
        id: openDialog
        onAccepted: openFileRequest(fileUrl)
    }

    MessageDialog {
        id: messageDialog
        title: "State machine info"
        icon: StandardIcon.Information
        text: "some text"
        Component.onCompleted: visible = false
        onYes: visible = false
    }

    Timer {
        id: stepTimer
        interval: 500; running: false; repeat: true
        onTriggered: singleStepAction()
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
            Action { text: qsTr("Compile"); onTriggered: compileAction() }
            MenuSeparator { id: menuSeparator }
            Action { text: qsTr("Single step"); onTriggered: singleStepAction() }
            Action { text: qsTr("Auto step"); onTriggered: stepTimer.running = !stepTimer.running }
        }
    }

    ScrollView {
        id: tapeScrollView
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
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    ScrollView {
        id: textEditScrollView
        x: 49
        y: 129
        width: 198
        height: 292
        clip: true

        TextEdit {
            id: textEdit
            objectName: "textEdit"
            text: qsTr("Text Edit")
            anchors.fill: parent
            //        anchors.right: menuSeparator.right
            //anchors.horizontalCenterOffset: 89
            font.pixelSize: 14
            //anchors.horizontalCenter: menuSeparator.horizontalCenter
        }
    }

    ScrollView {
        id: graphScrollView
        x: 391
        y: 140
        width: 200
        height: 291

        ListView {
            id: graphView
            anchors.fill: parent
            objectName: "graphView"
            model: graphModel
            delegate: Rectangle {
                    height: 25
                    width: 100
                    Text { text: modelData }
                }
//            delegate: TextField {
//                x: 5
//                width: 80
//                height: 40
//                Row {
//                    Text {
//                        text: modelData
//                        anchors.verticalCenter: parent.verticalCenter
//                    }
//                }
//            }
        }
    }


}
