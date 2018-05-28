/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property bool configurationError: false

//    LavaLamp {
//        id: lamp
//        anchors.centerIn: parent
//        bubbling: true
//    }

//    ButtonGroup {
//        buttons: column.children
//    }

//    Column {
//        id: column

//        spacing: 16

//        RadioButton {
//            checked: true
//            text: "success"
//            onCheckedChanged: if (checked) lamp.state = "success"
//        }

//        RadioButton {
//            text: "running"
//            onCheckedChanged: if (checked) lamp.state = "running"
//        }

//        RadioButton {
//            text: "failed"
//            onCheckedChanged: if (checked) lamp.state = "failed"
//        }
//    }

    LavaLampDashBoard {
        anchors.fill: parent
        model: buildsModel
    }

    Rectangle {
        anchors.fill: parent
        visible: root.configurationError

        Text {
            anchors {
                fill: parent
                margins: 80
            }
            font.pixelSize: 42
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
