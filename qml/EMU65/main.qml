import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 800
    height: 380
    title: "EMU65"

    menuBar: MenuBar {
        Menu {
            title: qsTr("Computer")
            MenuItem {
                text: qsTr("Power ON/OFF")
            }
            MenuItem {
                text: qsTr("Reset")
                /*onTriggered: aim65.resetButton = true*/
                onTriggered: aim65Controller.Start()
            }
            MenuItem {
                text: qsTr("Toggle RUN/STEP Mode")
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("Documentation")
            }
            MenuItem {
                text: qsTr("About")
            }
        }
    }

    /* 800 x 380 */
    Image {
        id: whiteBackground
        anchors.top: parent.top
        width: parent.width
        height: parent.height / 2
        source: "../../res/img/top-section.png"
    }

    Image {
        anchors.top: whiteBackground.bottom
        width: parent.width
        height: parent.height / 2
        source: "../../res/img/bottom-section.png"
    }

    Rectangle {
        id: switchPanel
        width: 180
        height: 100
        x: 10
        y: 160
        color: qsTr("transparent")

        Rectangle {
            id: rstRunKbRect
            width: switchPanel.width
            height: 25
            anchors.top : switchPanel.top
            anchors.left: switchPanel.left
            color: qsTr("black")
            Text {
                text: qsTr("RESET")
                color: qsTr("white")
                anchors.top: rstRunKbRect.top
                anchors.left: rstRunKbRect.left
                anchors.topMargin: 5
                anchors.leftMargin: 20
            }

            Text {
                text: qsTr("RUN")
                color: qsTr("white")
                anchors.top: rstRunKbRect.top
                anchors.horizontalCenter: rstRunKbRect.horizontalCenter
                anchors.topMargin: 5
            }

            Text {
                text: qsTr("KB")
                color: qsTr("white")
                anchors.top: rstRunKbRect.top
                anchors.right: rstRunKbRect.right
                anchors.rightMargin: 30
                anchors.topMargin: 5
            }
        }

        Rectangle
        {
            id: stepTtyRect
            width: switchPanel.width * (2/3)
            height: 25
            anchors.bottom : switchPanel.bottom
            anchors.right: switchPanel.right
            color: qsTr("black")
            Text {
                text: qsTr("STEP")
                color: qsTr("white")
                anchors.bottom: stepTtyRect.bottom
                anchors.left: stepTtyRect.left
                anchors.horizontalCenter: stepTtyRect.horizontalCenter
                anchors.leftMargin: 15
                anchors.bottomMargin: 5
            }

            Text {
                text: qsTr("TTY")
                color: qsTr("white")
                anchors.bottom: stepTtyRect.bottom
                anchors.right: stepTtyRect.right
                anchors.rightMargin: 30
                anchors.bottomMargin: 5
            }
        }

        Image {
            id: resetBtn
            width: 50
            height: 50
            source: "../../res/img/button-image.png"
            anchors.verticalCenter: switchPanel.verticalCenter
            anchors.left: switchPanel.left
            anchors.leftMargin: 10

            MouseArea {
                anchors.fill : parent
                onClicked: /* aim65.resetButton = true */ aim65Controller.Start()
            }
        }

        Image {
            id: runStepBtn
            width: 50
            height: 50
            source: "../../res/img/switch-image.png"
            anchors.horizontalCenter: switchPanel.horizontalCenter
            anchors.verticalCenter: switchPanel.verticalCenter

            MouseArea {
                anchors.fill : parent
                /*onPressed: parent.color = qsTr("white")
                onReleased: parent.color = qsTr("black")*/
            }
        }

        Image {
            id: kbTtyBtn
            width: 50
            height: 50
            source: "../../res/img/switch-image.png"
            anchors.verticalCenter: switchPanel.verticalCenter
            anchors.right: switchPanel.right
            anchors.rightMargin: 10
        }
    }

    Rectangle {
        width: 550
        height: 180
        anchors.left: switchPanel.right
        anchors.leftMargin: 20
        color: qsTr("black")
        y: 50

        Rectangle {
            id: display
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.horizontalCenter: parent.Center
            height: 80
            width: 520
            border.color: qsTr("white")
            border.width: 2
            color: qsTr("black")

            Text {
                id: ledScreen
                text: {
                    qsTr(ledDisplay.GetLedDisplay())
                }
                color: qsTr("red")
                font.pointSize: 30
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter

                Connections {
                    target: ledDisplay
                    onDisplayDigitChanged: {
                        ledScreen.text = qsTr(ledDisplay.GetLedDisplay())
                    }
                }
            }
        }

        Image {
            source: "../../res/img/rockwell-brand.png"
            width: 200
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 13
        }
    }

    Item {
        id: keyRegistrar
        focus: true
        anchors.fill: parent
        Keys.onPressed: {
            keyboard.pressedKey = event.key
            event.accepted = true
        }
    }
}
