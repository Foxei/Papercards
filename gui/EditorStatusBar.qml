import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "scripts/MaterialDesign.js" as MD
import "components/" as Components

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

    RowLayout {
        anchors.fill: parent

        Label {
            text: message
        }

        RowLayout {
            spacing: 0
            Layout.alignment: Qt.AlignRight

             Components.MaterialToolButton {
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
                focusPolicy: Qt.NoFocus

                onMoved: statusBar.scaleFactor = value;
            }

            Components.MaterialToolButton {
                text: MD.icons.zoom_in
                ToolTip.text: "Zoom in"
                onClicked: zoom(0.1)
            }
        }
    }
}
