import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "../basics/MaterialDesign.js" as MD
import "../basics/" as Basics

Pane {
    property real scaleFactor: 1.0
    property real maxScaleFactor: 1.5
    property real minScaleFactor: 0.5
    property string message: "Ready!"

    topPadding: 0; bottomPadding: 0

    onScaleFactorChanged: {
        sliderScaleFactor.value = scaleFactor;
    }

    function zoom(value){
        var newScaleFactor = scaleFactor + value;
        if(newScaleFactor > maxScaleFactor){
            newScaleFactor = maxScaleFactor;
        }else if(newScaleFactor < minScaleFactor){
            newScaleFactor = minScaleFactor;
        }
        scaleFactor = newScaleFactor;
    }

    FontLoader {
        id: iconFont
        source: "qrc:/assets/MaterialIcons-Regular.ttf"
    }

    RowLayout {
        anchors.fill: parent

        Label {
            text: message
        }

        RowLayout {
            spacing: 0
            Layout.alignment: Qt.AlignRight

             Basics.MaterialToolButton {
                text: MD.icons.zoom_out
                ToolTip.text: "Zoom out"
                onClicked: zoom(-0.1)
            }

            Slider {
                id: sliderScaleFactor

                from: minScaleFactor
                to: maxScaleFactor
                stepSize:0.01
                value: scaleFactor
                snapMode: Slider.SnapAlways

                onMoved: statusBar.scaleFactor = value;
            }

            Basics.MaterialToolButton {
                text: MD.icons.zoom_in
                ToolTip.text: "Zoom in"
                onClicked: zoom(0.1)
            }
        }
    }
}
