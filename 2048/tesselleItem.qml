import QtQuick 2.0

Item {
    property alias nombre: nombre
    property alias tesselle1: tesselle1
    Rectangle {
        id: tesselle1
        color: "#edebe7"
        radius: 2
        anchors.fill: parent

        Text {
            id: nombre
            height: 40
            color: "#78726d"
            text: qsTr("2")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            rotation: 0
            font.pixelSize: 38
            font.bold: true
            font.family: "Arial"
        }
    }
}
