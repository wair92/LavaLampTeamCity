/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

import QtQuick 2.8

GridView {
    id: grid

    cellWidth: 400;
    cellHeight: 400

    onCountChanged: console.log(count)

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
            text: Name
        }
    }
}
