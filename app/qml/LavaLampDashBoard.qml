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
        property string lastCommitee: ""
        width: grid.cellWidth
        height: grid.cellHeight

        LavaLamp {
            id: lamp
            anchors.top: parent.top
            anchors.bottom: item.top
            anchors.left: parent.left
            anchors.right: parent.right
            //anchors.horizontalCenter: parent
            bubbling: true
            labelText: Name
            status: Status

        }
        Item{
            id: item
            anchors.bottom: parent.bottom
            //anchors.horizontalCenter: parent
            width: lamp.width
            height: parent.height / 8
            Image{
                source: "../images/plaque.png"
                anchors.fill: parent
                Text{
                    anchors.centerIn: parent
                    text: LastCommitee
                    color: "blue"
                }
            }
        }
    }
}
