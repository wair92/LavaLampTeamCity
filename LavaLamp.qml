/*
    Original source code of this component (original name QUItBattery.qml) was taken from
    http://quitcoding.com/?page=work#quitbattery and is licensed under Creative Commons
    Attribution 3.0 Unported.
    Original author contact: info@quitcoding.com

    However this implementation contains lot of changes/deletions/enhancements compared to
    the original.
*/
import QtQuick 2.9
import QtQuick.Particles 2.0

Item {
    id: root

    property string text: ""
    property string style: "normal" // "running", "error"
    property bool bubbling: false

    width: batteryImage.width
    height: batteryImage.height

    Image {
        id: tubBar
        source: "images/tub_bar.png"
        visible: false
    }

    ParticleSystem {
        id: particlesItem
        anchors.fill: tubBar
        running: root.bubbling

        ImageParticle {
            source: "images/particle.png"
            rotationVariation: 180
            color:"#ffffff"
            colorVariation: 0.2
        }

        Emitter {
            width: 8
            height: parent.height
            x: 20
            emitRate: root.style === "normal" ? 1
                                              : root.style === "running" ? 10
                                                                         : 50
            lifeSpan: 3500
            size: 32
            sizeVariation: 24
            velocity: PointDirection{ x: 5 + 100; xVariation: x * 0.5; yVariation: 6 }
            endSize: 8

        }

        Turbulence {
            width: parent.width
            height: parent.height
            strength: 32
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
        property real red: root.style === "normal" ? 0.0 : 1.0
        property real green: root.style === "error" ? 0.0 : 1.0

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
        id: batteryImage
        source: "images/tub.png"
    }

    Text {
        anchors.centerIn: parent
        y: 22
        font.pixelSize: 48
        style: Text.Outline
        color: "#404040"
        styleColor: "#ffffff"
        font.bold: true
        rotation: -root.rotation
        text: root.text
        SequentialAnimation on opacity {
            running: root.style === "error"
            loops: Animation.Infinite
            alwaysRunToEnd: true
            NumberAnimation { to: 0.5; duration: 200; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 1.0; duration: 200; easing.type: Easing.InOutQuad }
        }
    }
}
