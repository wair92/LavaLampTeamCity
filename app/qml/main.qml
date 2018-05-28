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

    property string configurationError: false

    LavaLamp {
        id: lamp
        anchors.centerIn: parent
        bubbling: true
    }

    ButtonGroup {
        buttons: column.children
    }

    Column {
        id: column

        spacing: 16

        RadioButton {
            checked: true
            text: "normal"
            onCheckedChanged: if (checked) lamp.state = "normal"
        }

        RadioButton {
            text: "running"
            onCheckedChanged: if (checked) lamp.state = "running"
        }

        RadioButton {
            text: "error"
            onCheckedChanged: if (checked) lamp.state = "error"
        }
    }

    Rectangle {
        anchors.fill: parent
        visible: root.configurationError

        Text {
            font.pixelSize: 32
            style: Text.Outline
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "red"
            styleColor: "black"
            text: "Configuration error: either provide absolute path to config.json file\n" +
                  "as application argument or save config.json file next" +
                  "to application executable."
        }
    }
}
