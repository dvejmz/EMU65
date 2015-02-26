import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: "EMU65 Debugger"

    Rectangle {
        id: aimInspectorArea
        width: parent.width
        height: parent.height
        x: 0
        y: 0

        Text {
            id: aimInspCpu
            text: qsTr("CPU Status: ") + aimInspector.cpuStatus

            Connections {
                target: aimInspector
                onCpuStatusChanged: {
                    aimInspCpu.text = qsTr("CPU Status: ") + aimInspector.cpuStatus
                }
            }
        }

        Text {
            id : aimInspComponent
            anchors.top: aimInspCpu.bottom
            text : qsTr("Memory Contents\n")

            Connections {
                target: aimInspector
                onComponentStatusChanged: {
                    aimInspComponent.text = qsTr("Memory Contents\n") + aimInspector.componentStatus
                }
            }
        }

        Text {
            id: aimInspLed
            anchors.left : aimInspCpu.right
            anchors.leftMargin: 10
            text: qsTr("LED Registers\n")

            Connections {
                target: aimInspector
                onLedStatusChanged: {
                    aimInspLed.text = qsTr("LED Registers\n") + aimInspector.ledStatus
                }
            }
        }

        Text {
            id: aimInspPrinter
            anchors.left : aimInspKeyboard.right
            anchors.leftMargin: 10
            text: qsTr("Printer Registers:\n")

            Connections {
                target: aimInspector
                onPrinterStatusChanged: {
                    aimInspPrinter.text = qsTr("Printer Registers:\n") + aimInspector.printerStatus
                }
            }
        }

        Text {
            id: aimInspKeyboard
            anchors.left : aimInspLed.right
            anchors.leftMargin: 10
            text: qsTr("Keyboard Registers\n")

            Connections {
                target: aimInspector
                onKeyboardStatusChanged: {
                    aimInspKeyboard.text = qsTr("Keyboard Registers\n") + aimInspector.keyboardStatus
                }
            }
        }
    }
}
