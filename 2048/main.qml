import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14

ApplicationWindow {
    id: frame
    visible: true
    width: 400
    height: 500
    color: "#faf8f0"
    title: qsTr("2048")


    menuBar: MenuBar {
            Menu {
                title: qsTr("Partie")
                Action {
                    text: qsTr("Nouvelle partie (Ctrl+N)")
                    shortcut: "Ctrl+N"
                    onTriggered: vueObjPlat.init()}
                Action {
                    text: qsTr("Retour arrière (Ctrl+Z)")
                    shortcut: "Ctrl+Z"
                    onTriggered: vueObjPlat.undo()}
                Action {
                    text: qsTr("Retour avant (Ctrl+Y)")
                    shortcut: "Ctrl+Y"
                    onTriggered: vueObjPlat.redo()}
                Action {
                    text: qsTr("Remettre meilleur score à zéro")
                    onTriggered: vueObjPlat.reset_best()}
                MenuSeparator { }
                Action { text: qsTr("Quit") }

                focus : false
            }

            Menu {
                title: qsTr("Personnaliser")
                Menu {
                    title: qsTr("Base")
                    Action {
                        text: qsTr("2")
                        onTriggered: vueObjPlat.changer_base(2)}
                    Action {
                        text: qsTr("3")
                        onTriggered: vueObjPlat.changer_base(3)}
                    Action {
                        text: qsTr("5")
                        onTriggered: vueObjPlat.changer_base(5)}
                    Action {
                        text: qsTr("7")
                        onTriggered: vueObjPlat.changer_base(7)}
                    Action {
                        text: qsTr("11")
                        onTriggered: vueObjPlat.changer_base(11)}
                }
                Menu {
                    title: qsTr("Couleurs")
                    Action {
                        text: qsTr("Rouge/Jaune classique")
                        icon.color: "red"
                        onTriggered: vueObjPlat.changer_couleurs(1)}
                    Action {
                        text: qsTr("Bleu/Vert")
                        onTriggered: vueObjPlat.changer_couleurs(2)}
                    Action {
                        text: qsTr("Jaune/Vert")
                        onTriggered: vueObjPlat.changer_couleurs(3)}
                }

                focus : false
            }

            focus : false
    }


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
        focus: true

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Up:
                vueObjPlat.move(3);
                break;
            case Qt.Key_Down:
                vueObjPlat.move(4);
                break;
            case Qt.Key_Left:
                vueObjPlat.move(1);
                break;
            case Qt.Key_Right:
                vueObjPlat.move(2);
                break;
            }
        }
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
                color: vueObjPlat.couleurQML[0]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[0]
                Text {
                    id: nombre1
                    color: vueObjPlat.couleurtextQML[0]
                    text: vueObjPlat.nombreQML[0]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    fontSizeMode: Text.HorizontalFit
                    font.bold: true
                    font.family: "Arial"
                }
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

            Rectangle {
                id: tesselle2
                color: vueObjPlat.couleurQML[1]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[1]
                Text {
                    id: nombre2
                    color: vueObjPlat.couleurtextQML[1]
                    text: vueObjPlat.nombreQML[1]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    fontSizeMode: Text.HorizontalFit
                    font.bold: true
                    font.family: "Arial"
                }
            }
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

            Rectangle {
                id: tesselle3
                color: vueObjPlat.couleurQML[2]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[2]
                Text {
                    id: nombre3
                    color: vueObjPlat.couleurtextQML[2]
                    text: vueObjPlat.nombreQML[2]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle4
                color: vueObjPlat.couleurQML[3]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[3]
                Text {
                    id: nombre4
                    color: vueObjPlat.couleurtextQML[3]
                    text: vueObjPlat.nombreQML[3]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle5
                color: vueObjPlat.couleurQML[4]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[4]
                Text {
                    id: nombre5
                    color: vueObjPlat.couleurtextQML[4]
                    text: vueObjPlat.nombreQML[4]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle6
                color: vueObjPlat.couleurQML[5]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[5]
                Text {
                    id: nombre6
                    color: vueObjPlat.couleurtextQML[5]
                    text: vueObjPlat.nombreQML[5]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle7
                color: vueObjPlat.couleurQML[6]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[6]
                Text {
                    id: nombre7
                    color: vueObjPlat.couleurtextQML[6]
                    text: vueObjPlat.nombreQML[6]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle8
                color: vueObjPlat.couleurQML[7]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[7]
                Text {
                    id: nombre8
                    color: vueObjPlat.couleurtextQML[7]
                    text: vueObjPlat.nombreQML[7]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle9
                color: vueObjPlat.couleurQML[8]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[8]
                Text {
                    id: nombre9
                    color: vueObjPlat.couleurtextQML[8]
                    text: vueObjPlat.nombreQML[8]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle10
                color: vueObjPlat.couleurQML[9]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[9]
                Text {
                    id: nombre10
                    color: vueObjPlat.couleurtextQML[9]
                    text: vueObjPlat.nombreQML[9]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle11
                color: vueObjPlat.couleurQML[10]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[10]
                Text {
                    id: nombre11
                    color: vueObjPlat.couleurtextQML[10]
                    text: vueObjPlat.nombreQML[10]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle12
                color: vueObjPlat.couleurQML[11]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[11]
                Text {
                    id: nombre12
                    color: vueObjPlat.couleurtextQML[11]
                    text: vueObjPlat.nombreQML[11]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle13
                color: vueObjPlat.couleurQML[12]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[12]
                Text {
                    id: nombre13
                    color: vueObjPlat.couleurtextQML[12]
                    text: vueObjPlat.nombreQML[12]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle14
                color: vueObjPlat.couleurQML[13]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[13]
                Text {
                    id: nombre14
                    color: vueObjPlat.couleurtextQML[13]
                    text: vueObjPlat.nombreQML[13]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle15
                color: vueObjPlat.couleurQML[14]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[14]
                Text {
                    id: nombre15
                    color: vueObjPlat.couleurtextQML[14]
                    text: vueObjPlat.nombreQML[14]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
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

            Rectangle {
                id: tesselle16
                color: vueObjPlat.couleurQML[15]
                radius: 2
                anchors.fill: parent
                visible: vueObjPlat.visibleQML[15]
                Text {
                    id: nombre16
                    color: vueObjPlat.couleurtextQML[15]
                    text: vueObjPlat.nombreQML[15]
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    rotation: 0
                    font.pixelSize: 38
                    font.bold: true
                    font.family: "Arial"
                    fontSizeMode: Text.HorizontalFit
                }
            }
        }

        Rectangle {
            id: perdu
            x: 174
            y: 257
            color: "#cac0b5"
            visible: vueObjPlat.finPartieQML[1]
            opacity: 0.641
            anchors.fill: parent

            Text {
                id: textPerdu
                text: qsTr("Perdu !")
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 20
            }
        }

        Rectangle {
            id: gagne
            x: 177
            y: 256
            color: "#cac0b5"
            opacity: 0.641
            anchors.fill: parent
            visible: vueObjPlat.finPartieQML[0]
            Text {
                id: textGagne
                text: qsTr("Gagné !")
                font.bold: true
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                anchors.horizontalCenter: parent.horizontalCenter
            }
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
            id: best_label
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

        Text {
            id: score_best
            x: 18
            y: 19
            text: vueObjPlat.scoresQML[1]
            font.pixelSize: 14
            color: "#f9f6f2"
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            rotation: 0
            font.bold: true
            font.family: "Arial"
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
            id: score_label
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

        Text {
            id: score_current
            x: 18
            y: 20
            text: vueObjPlat.scoresQML[0]
            font.pixelSize: 14
            color: "#f9f6f2"
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            rotation: 0
            font.bold: true
            font.family: "Arial"
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
            color: "#e8ded6"
            text: qsTr("New Game")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.bold: true
            renderType: Text.NativeRendering
            font.pixelSize: 13
        }

        MouseArea {
            id: mouseArea_new_game
            width: 89
            height: 28
            onClicked: vueObjPlat.init()
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
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
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
            Action {
                shortcut: "Ctrl+Z"
                onTriggered: vueObjPlat.undo()
            }
        }

        MouseArea {
            id: mouseArea_undo
            width: 26
            height: 28
            onClicked: vueObjPlat.undo()
        }
    }

    Rectangle {
        id: rect_redo
        x: 62
        y: 71
        width: 26
        height: 28
        color: "#786d66"
        radius: 2
        Text {
            id: redo
            color: "#e8ded6"
            text: "↩︎"
            transformOrigin: Item.Center
            z: 0
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottomMargin: 4
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            anchors.rightMargin: 3
            font.pixelSize: 17
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            font.weight: Font.ExtraLight
            anchors.topMargin: 4
            anchors.leftMargin: 3
            renderType: Text.NativeRendering
            rotation: 180
            Action {
                shortcut: "Ctrl+Z"
            }
        }

        MouseArea {
            id: mouseArea_redo
            width: 26
            height: 28
            onClicked: vueObjPlat.redo()
        }
    }

}

/*##^##
Designer {
    D{i:5;anchors_height:40}D{i:4;anchors_height:75;anchors_width:75}D{i:2;anchors_height:293;anchors_width:329;anchors_x:30;anchors_y:109}
D{i:22;anchors_y:2}D{i:24;anchors_y:2}D{i:26;anchors_x:"-101";anchors_y:2}D{i:29;anchors_height:20;anchors_x:3;anchors_y:4}
}
##^##*/
