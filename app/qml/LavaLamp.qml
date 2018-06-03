/*
    Original source code of this component (original name QUItBattery.qml) was taken from
    http://quitcoding.com/?page=work#quitbattery and is licensed under Creative Commons
    Attribution 3.0 Unported.
    Original author contact: info@quitcoding.com

    However this implementation contains lot of changes/deletions/enhancements compared to
    the original.
*/

import QtQuick 2.8
import QtQuick.Particles 2.0

Item {
    id: root

    property string text: ""
    property string status: "success" // "running", "failed"
    property bool bubbling: false

    Image {
        id: tubBar
        anchors {
            centerIn: tubImage
            horizontalCenterOffset: tubImage.paintedWidth * 0.02
        }
        source: "../images/tub_bar2.png"
        visible: false
        width: tubImage.paintedWidth * 0.92
        height: tubImage.paintedHeight * 0.9
        fillMode: Image.PreserveAspectFit
    }

    ParticleSystem {
        id: particlesItem
        anchors.fill: tubBar

        ImageParticle {
            id: bubble
            anchors.fill: parent
            source: "../images/bubble.png"
            opacity: 0.4
        }

        Wander {
            xVariance: 25;
            pace: 25;
        }

        Emitter {
            id: emitter
            property real yAccel: root.status === "success" ? -8
                                                            : root.status === "running" ? -20
                                                                                        : -80

            width: parent.width
            height: 150
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            emitRate: root.status === "success" ? 0.25
                                                : root.status === "running" ? 4
                                                                            : 15
            lifeSpan: 15000
            acceleration: PointDirection{ y: emitter.yAccel; xVariation: 6; yVariation: 2 }
            size: 32
            sizeVariation: 24
        }
    }

    ShaderEffectSource {
        id: particlesShaderSource
        anchors.fill: particlesItem
        sourceItem: particlesItem
        hideSource: true
        visible: false
    }

    ShaderEffect {
        id: shaderEffectItem
        anchors.fill: particlesShaderSource

        property variant source: tubBar
        property variant source2: particlesShaderSource
        property real red: root.status === "success" ? 0.0 : 1.0
        property real green: root.status === "failed" ? 0.0 : 1.0

        fragmentShader: "
            uniform sampler2D source;
            uniform sampler2D source2;
            uniform lowp float qt_Opacity;
            varying highp vec2 qt_TexCoord0;
            uniform highp float red;
            uniform highp float green;
            void main() {
                lowp vec4 pix = texture2D(source, qt_TexCoord0);
                lowp vec4 pix2 = texture2D(source2, qt_TexCoord0);
                highp float r = qt_TexCoord0.y*0.008 - 0.004;
                highp float isVis = smoothstep(qt_TexCoord0.x-0.02-r, qt_TexCoord0.x+0.02-r, 1.0);
                highp vec4 color = vec4(red, green, 0.0, 1.0);
                highp vec4 light =  color * isVis * pix;
                gl_FragColor = (isVis * pix.a * pix2 + light) * qt_Opacity;
            }"
    }

    Image {
        id: tubImage
        anchors.fill: parent
        source: "../images/tub3.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        anchors {
            centerIn: parent
            verticalCenterOffset: -tubImage.paintedHeight * 0.05
        }
        font.pixelSize: tubImage.paintedWidth * 0.15
        font.bold: true
        width: tubImage.paintedWidth
        style: Text.Outline
        color: "#404040"
        styleColor: "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        text: root.text
        SequentialAnimation on opacity {
            running: root.status === "failed"
            loops: Animation.Infinite
            alwaysRunToEnd: true
            NumberAnimation { to: 0.5; duration: 200; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 1.0; duration: 200; easing.type: Easing.InOutQuad }
        }
    }
}
