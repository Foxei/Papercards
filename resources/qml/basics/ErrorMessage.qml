import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Shapes 1.14

Pane {
    id: errorMessageBasePane
    anchors.top: parent.top
    anchors.right: parent.right

    width: parent.width
    padding: 0
    z: 200

    opacity: 0.0
    visible: false

    function fade(show){
        if(show){
            errorMessageBasePane.opacity = 1.0;
            errorMessageBasePane.scale = 1.0;
            errorMessageBasePane.visible = true;
        }else{
            errorMessageBasePane.opacity = 0.0;
            errorMessageBasePane.scale = 0.0;
        }
    }
    Behavior on opacity {
        PropertyAnimation{
            duration: 200
            onRunningChanged: {
                if(!running && errorMessageBasePane.opacity == 0.0){
                    errorMessageBasePane.visible = false;
                }else{
                    errorMessageBasePane.visible = true;
                }
            }
        }
    }
    Behavior on scale {
        PropertyAnimation{
            duration: 200
            easing.type: Easing.InOutElastic;
            easing.amplitude: 1.0;
            easing.period: 1.5
        }
    }

    RowLayout{
        anchors.fill: parent
        Pane {
            Layout.fillWidth: true
            Layout.rightMargin: 15

            Material.theme: Material.Dark
            Material.elevation: 6
            RowLayout{
                anchors.fill: parent
                Label{
                    Layout.preferredWidth: parent.width
                    wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                    font.pointSize: 12
                    text: "A card should always contain only the smallest possible amount of text, yet the most important information should always be included and only the most important."
                }
                Shape {
                    width: 30
                    height: 30
                    layer.samples: 8
                    layer.enabled: true
                    transform: Translate{x:7}
                    ShapePath {
                        strokeColor: Material.background
                        strokeWidth: 3
                        fillColor: Material.background
                        capStyle: ShapePath.RoundCap
                        startX: -3; startY: 0
                        PathLine { x: -3; y: 30 }
                        PathLine { x: 15; y: 15 }
                        PathLine { x: -3; y: 0 }
                    }
                }
            }
        }
        ErrorIcon{
            Layout.preferredHeight: 24
            Layout.preferredWidth: 24
            iconSource: "qrc:/assets/error.png"
        }
    }
}
