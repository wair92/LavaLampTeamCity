/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

import QtQuick 2.8

GridView {
    id: grid

    cellWidth: 400
    cellHeight: 500

    delegate: Item {
        width: grid.cellWidth
        height: grid.cellHeight

        LavaLamp {
            id: lamp
            anchors.fill: parent
            bubbling: true
            status: Status
        }

        Text {
            id: name
            anchors {
                horizontalCenter: lamp.horizontalCenter
                bottom: lamp.bottom
                bottomMargin: 20
            }
            height: lamp.height * 0.15
            width: lamp.height * 0.5
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: Name
            color: "red"
            font.bold: true
        }
    }
}
