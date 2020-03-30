import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: frame
    visible: true
    width: 400
    height: 500
    color: "#faf8f0"
    title: qsTr("2048")

    Text {
        id: titre
        height: 40
        color: "#89817a"
        text: qsTr("2048")
        rotation: 0
        anchors.top: parent.top
        anchors.left: parent.left
        font.bold: true
        anchors.leftMargin: 30
        font.family: "Arial"
        font.pixelSize: 38
        anchors.topMargin: 20
    }

    Rectangle {
        id: table
        width: 340
        height: 340
        color: "#ab9a8d"
        layer.smooth: false
        smooth: true
        anchors.top: parent.top
        anchors.topMargin: 110
        anchors.left: parent.left
        anchors.leftMargin: 30
        radius : 2

        Rectangle {
            id: case1
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            radius : 2
            opacity: 0.8

            Rectangle {
                id: tesselle1
                color: "#edebe7"
                radius: 2
                anchors.fill: parent
            }
        }

        Rectangle {
            id: case2
            x: -9
            y: -8
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 91
            anchors.topMargin: 8
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case3
            x: 2
            y: 7
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 174
            anchors.topMargin: 8
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case4
            x: 9
            y: -6
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 257
            anchors.topMargin: 8
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case5
            x: 0
            y: 0
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.topMargin: 91
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case6
            x: -9
            y: -8
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 91
            anchors.topMargin: 91
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case7
            x: 2
            y: 7
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 174
            anchors.topMargin: 91
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case8
            x: 9
            y: -6
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 257
            anchors.topMargin: 91
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case9
            x: -2
            y: -2
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.topMargin: 174
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case10
            x: -11
            y: -10
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 91
            anchors.topMargin: 174
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case11
            x: 0
            y: 5
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 174
            anchors.topMargin: 174
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case12
            x: 7
            y: -8
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 257
            anchors.topMargin: 174
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case13
            x: -2
            y: -2
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 8
            anchors.topMargin: 257
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case14
            x: -11
            y: -10
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 91
            anchors.topMargin: 257
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case15
            x: 0
            y: 5
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 174
            anchors.topMargin: 257
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: case16
            x: 7
            y: -8
            width: 75
            height: 75
            color: "#cac0b5"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 257
            anchors.topMargin: 257
            radius : 2
            opacity: 0.8
        }

        Rectangle {
            id: rectangle
            width: 200
            height: 200
            color: "#ffffff"
        }
    }

    Rectangle {
        id: rect_best_score
        x: -4
        y: 4
        width: 60
        height: 40
        color: "#cac0b5"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 310
        anchors.topMargin: 20
        radius : 2

        Text {
            id: best
            x: 18
            color: "#e8ded6"
            text: qsTr("BEST")
            renderType: Text.NativeRendering
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rect_current_score
        x: -12
        y: 5
        width: 60
        height: 40
        color: "#cac0b5"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 244
        anchors.topMargin: 20
        radius : 2

        Text {
            id: score
            x: -44
            y: 7
            color: "#e8ded6"
            text: qsTr("SCORE")
            anchors.top: parent.top
            renderType: Text.NativeRendering
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 2
            anchors.horizontalCenterOffset: 0
        }
    }

    Rectangle {
        id: rect_new_game
        x: 281
        y: 71
        width: 89
        height: 28
        color: "#7b6753"
        radius : 2

        Text {
            id: new_game
            x: -101
            y: 2
            color: "#e8ded6"
            text: qsTr("New Game")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            renderType: Text.NativeRendering
            font.pixelSize: 13
        }

        MouseArea {
            id: mouseArea_new_game
            width: 89
            height: 28
        }
    }

    Rectangle {
        id: rect_undo
        x: 30
        y: 71
        width: 26
        height: 28
        color: "#786d66"
        radius : 2
        Text {
            id: undo
            color: "#e8ded6"
            text: qsTr("↪︎")
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
            rotation: 180
            font.weight: Font.ExtraLight
            renderType: Text.NativeRendering
            font.bold: true
            font.pixelSize: 17
        }

        MouseArea {
            id: mouseArea_undo
            width: 23
            height: 28
        }
    }
}

/*##^##
Designer {
    D{i:4;anchors_height:75;anchors_width:75}D{i:2;anchors_height:293;anchors_width:329;anchors_x:30;anchors_y:109}
D{i:22;anchors_y:2}D{i:24;anchors_y:2}D{i:26;anchors_x:"-101";anchors_y:2}D{i:29;anchors_height:20;anchors_x:3;anchors_y:4}
}
##^##*/
