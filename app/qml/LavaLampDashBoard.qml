/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

import QtQuick 2.8

GridView {
    id: grid
    anchors.fill: parent
    cellWidth: 200;
    cellHeight: 200

    model: buildsModel
    delegate: Item {
        width: grid.cellWidth
        height: grid.cellHeight

        LavaLamp {
            id: lamp
            anchors.fill: parent
            bubbling: true
        }
    }
}
