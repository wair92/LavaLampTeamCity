/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

import QtQuick 2.5
import QtQuick.Window 2.3
import QtQuick.Controls 2.1

Window {
    id: root

    visible: true
    width: 1920
    height: 300
    title: qsTr("TeamCity Lava Lamp 1.0")
    color: "black"
    flags: Qt.SplashScreen | Qt.WindowStaysOnTopHint
    screen: Qt.application.screens[1]

    x: screen.virtualX
    y: screen.virtualY + Screen.height - height

    property bool configurationError: false
    property int buildInfoColumns: 2

    LavaLampDashBoard {
        anchors.topMargin: 100
        anchors.fill: parent
        model: buildsModel
        colums: root.buildInfoColumns
    }

    Rectangle {
        anchors.fill: parent
        visible: root.configurationError

        Text {
            anchors {
                fill: parent
                margins: 80
            }
            font.pixelSize: 46
            style: Text.Outline
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "red"
            styleColor: "black"
            wrapMode: Text.WordWrap
            text: "Configuration error: either provide absolute path to config.json file " +
                  "as application argument or save config.json file next " +
                  "to application executable."
        }
    }
}
