import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.1

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 800
    height: 480
    minimumHeight: 350
    minimumWidth: 650
    title: qsTr("Turing Machine Simulator")
    signal openFileRequest(var url)
    signal compileAction()
    signal singleStepAction()
    signal autoStepAction()
    signal headMoved(var position)

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
            MenuSeparator { }
            Action { text: qsTr("&Save") }
            Action { text: qsTr("Save &As...") }
        }
        Menu {
            title: qsTr("&Run")
            Action { text: qsTr("Compile"); onTriggered: compileAction(); shortcut: Qt.Key_F5 }
            MenuSeparator { }
            Action { text: qsTr("Single step"); onTriggered: singleStepAction(); shortcut: Qt.Key_F6 }
            Action {
                text: qsTr("Auto step")
                onTriggered: stepTimer.running = !stepTimer.running
                shortcut: "Ctrl+R"
            }
        }
    }

    ScrollView {
        id: tapeScrollView
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 49
        anchors.left: parent.left
        anchors.leftMargin: 49
        anchors.top: parent.top
        anchors.topMargin: 18
        clip: true

        ListView {
            id: tapeView
            anchors.fill: parent
            highlightMoveDuration: 50
            orientation: ListView.Horizontal
            model: tapeModel
            interactive: true
            clip: true
            delegate: Item  {
                id: tapeTextField
                width: 35
                height: tapeView.height
                TextField {
                    id: textField
                    text: name
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    //verticalCenter: parent.verticalCenter
//                    horizontalCenter: parent.horizontalCenter

                    onEditingFinished: {
                        name = text;
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true

                    onClicked: {
                        textField.forceActiveFocus()
                        mouse.accepted = false;
                    }
                    onDoubleClicked: {
                        tapeView.currentIndex = index
                        headMoved(index)
                        mouse.accepted = false;
                    }
                }
            }
            highlight: Rectangle {
                height: tapeView.height
                width: 35
                color: "pink"
                opacity: 0.5
                clip: true
            }

            Connections {
                target: controllerObject
                onHeadPositionChanged: {
                    tapeView.currentIndex = newIndex
                }
            }
        }
    }

    ScrollView {
        id: textEditScrollView
        anchors.right: graphScrollView.left
        anchors.rightMargin: 24
        anchors.top: tapeScrollView.bottom
        anchors.topMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 22
        anchors.left: parent.left
        anchors.leftMargin: 49
        clip: true

        TextArea {
            id: textEdit
            objectName: "textEdit"
            text: qsTr("")
            anchors.topMargin: -8
            anchors.rightMargin: -403
            anchors.bottomMargin: 1
            anchors.fill: parent
            //        anchors.right: menuSeparator.right
            //anchors.horizontalCenterOffset: 89
            font.pixelSize: 14
            //anchors.horizontalCenter: menuSeparator.horizontalCenter
        }
    }

    ScrollView {
        id: graphScrollView
        x: 476
        width: 275
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 22
        anchors.right: parent.right
        anchors.rightMargin: 49
        anchors.top: tapeScrollView.bottom
        anchors.topMargin: 164
        clip: true

        ListView {
            id: graphView
            highlightMoveDuration: 50
            anchors.fill: parent
            objectName: "graphView"
            model: graphModel
            delegate: Item {
                height: 25
                width: graphScrollView.width
                //color: "transparent"
                Label { text: modelData }
                MouseArea {
                    anchors.fill: parent
                    onClicked: graphView.currentIndex = index
                }
            }

            highlight: Rectangle {
                height: 25
                width: graphScrollView.width
                clip: true
                color: "pink"
                opacity: 0.5
            }

            Connections {
                target: controllerObject
                onCommandIdChangeInGraph: {
                    graphView.currentIndex = newIndex
                }
            }
        }
    }

    Slider {
        id: slider
        x: 476
        y: 150
        width: 275
        height: 23
        wheelEnabled: true
        anchors.right: parent.right
        anchors.rightMargin: 49
        anchors.bottom: graphScrollView.top
        anchors.bottomMargin: 15
        stepSize: 10
        to: 1500
        from: 1
        value: 500
        onValueChanged: spinBox.value = value
    }

    SpinBox {
        id: spinBox
        x: 614
        y: 96
        width: 137
        height: 48
        font.pointSize: 12
        editable: true
        wheelEnabled: true
        anchors.right: parent.right
        anchors.rightMargin: 49
        anchors.bottom: slider.top
        anchors.bottomMargin: 6
        from: 1
        stepSize: 100
        to: 1500
        value: 500
        onValueChanged:  {
            slider.value = value
            stepTimer.interval = value
        }
    }

    Label {
        id: label
        x: 408
        y: 75
        width: 122
        height: 48
        text: qsTr("Step [ms]:")
        font.pointSize: 12
        anchors.bottom: slider.top
        anchors.bottomMargin: 6
        anchors.right: spinBox.left
        anchors.rightMargin: 16
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        id: label1
        x: 476
        y: 113
        width: 122
        height: 37
        text: qsTr("Alphabet:")
        anchors.right: alphabetEdit.left
        anchors.rightMargin: 16
        anchors.bottom: label.top
        anchors.bottomMargin: 6
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
    }

    TextField {
        id: alphabetEdit
        objectName: "alphabetEdit"
        x: 614
        y: 113
        width: 137
        height: 45
        text: qsTr("")
        anchors.right: parent.right
        anchors.rightMargin: 49
        anchors.bottom: spinBox.top
        anchors.bottomMargin: -2
        font.pointSize: 12
    }


}
