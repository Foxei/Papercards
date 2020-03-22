import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import QtGraphicalEffects 1.0

import "scripts/MaterialDesign.js" as MD

Dialog {
    id: savePopup

    title: "Are you sure want to discard all changes?"

    anchors.centerIn: Overlay.overlay
    modal: true
    focus: true
    standardButtons: Dialog.Apply | Dialog.Cancel
    closePolicy: Popup.CloseOnEscape

    RowLayout{
        spacing: 10
        anchors.fill: parent
        Label{
            Layout.alignment: Qt.AlignTop
            font.family: "Material Icons"
            font.pixelSize: 24
            text: MD.icons.warning;
        }
        Label{
            text: "All the new changed made to the deck<br>after the save will be lost."
        }
    }
    Component.onCompleted: {
        savePopup.standardButton(Dialog.Apply).text = "Discard";
        savePopup.standardButton(Dialog.Apply).clicked.connect(accept)
        savePopup.standardButton(Dialog.Cancel).text = "Cancle";
    }
}
