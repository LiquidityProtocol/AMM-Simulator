import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import LiquidityProtocol.Playground 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Playground {
        id: playground
    }

    Button {
        id: myButton
        anchors.centerIn: parent
        text: "Click Me"
        onClicked: playground.callMe()
    }
}
