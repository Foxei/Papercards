import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import QtGraphicalEffects 1.0

Dialog {
    id: aboutPopup
    anchors.centerIn: Overlay.overlay
    modal: true
    //focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    ColumnLayout{
        anchors.fill: parent
        Item{
            width: image.width
            height: image.height
            Layout.alignment: Qt.AlignHCenter
            Image {
                id: image
                source: "qrc:/resources/logo.png"
                anchors.centerIn: parent
                smooth: true
                visible: false
            }
            ColorOverlay {
                anchors.fill: image
                source: image
                color: Material.foreground
                cached: true
            }
        }

        TextArea{
            Layout.alignment: Qt.AlignHCenter
            textFormat: Label.RichText
            selectByMouse: true
            readOnly: true
            text: "<style>a:link { color: " + Material.accent + "; text-decoration: none;}</style><html>
<h1>Papercards</h1>
<p><small>Version "+Qt.application.version+"</small></p>
<p>This project is open source and<br/>contributions are welcomed.</p>
<p>Visit <a href=\"https://github.com/Foxei/Papercards\">https://github.com/Foxei/<br/>Papercards</a> for more information, to report<br/>a bug or to suggest a new feature.</p>
<p><small>Copyright © 2019-2020 Simon Schäfer. All<br/>rights reserved.</small></p>
</html>"
            horizontalAlignment: Label.AlignHCenter
            onLinkActivated: Qt.openUrlExternally(link)
        }

    }
}
