import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.14

Dialog {
    id: aboutPopup

    property color selectedColor

    function acceptColor(color){
        selectedColor = color;
        accept();
    }

    y:parent.height+20
    x: -17

    //focus: false
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    ColumnLayout{
        spacing: 0
        Shape {
            Layout.topMargin: 0
            Layout.bottomMargin: -30
            width: 30
            height: 30
            layer.samples: 8
            layer.enabled: true
            transform: Translate{y:-50}
            rotation: -90
            ShapePath {
                strokeColor: "#424242"
                strokeWidth: 3
                fillColor: "#424242"
                capStyle: ShapePath.RoundCap
                startX: -3; startY: 0
                PathLine { x: -3; y: 30 }
                PathLine { x: 15; y: 15 }
                PathLine { x: -3; y: 0 }
            }
        }

        GridLayout{
            columns: 3
            rows: 3
            Layout.margins: 0
            Button{
                Material.background: Material.primary
                text: "Auto"
                onClicked: acceptColor("#ffffff")
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Red
                onClicked: acceptColor(Material.color(Material.Red))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Pink
                onClicked: acceptColor(Material.color(Material.Pink))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Purple
                onClicked: acceptColor(Material.color(Material.Purple))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Blue
                onClicked: acceptColor(Material.color(Material.Blue))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Cyan
                onClicked: acceptColor(Material.color(Material.Cyan))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Green
                onClicked: acceptColor(Material.color(Material.Green))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Yellow
                onClicked: acceptColor(Material.color(Material.Yellow))
                focusPolicy: Qt.NoFocus
            }
            Button{
                Material.background: Material.Orange
                onClicked: acceptColor(Material.color(Material.Orange))
                focusPolicy: Qt.NoFocus
            }

        }
    }
}
