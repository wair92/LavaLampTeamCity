/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

import QtQuick 2.8

GridView {
    id: grid

    property int colums: 2

    cellWidth: width / Math.ceil( count / colums )
    cellHeight: height / colums

    delegate: Item {
        width: grid.cellWidth
        height: grid.cellHeight

        LavaLamp {
            id: lamp
            anchors.fill: parent
            bubbling: true
            labelText: Name
            status: Status
        }
    }
}
