import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtGraphicalEffects 1.14

import io.papercards.backend 1.0

import "components" as Components

ApplicationWindow {
    property real scaleFactor: 1.0

    id: root
    visible: true
    title: "Papercards"
    width: 800
    height: 600

    onActiveFocusControlChanged: {
        var focusObjectName = activeFocusControl.objectName;

        var cardFocused = focusObjectName.startsWith("card");
        toolBar.enableTextFunctions = cardFocused;

        var textAreaFocused = focusObjectName.startsWith("card-answer");
        toolBar.enableEditorFunctions = textAreaFocused;
    }

    onScaleFactorChanged: {
        cardView.scaleFactor = scaleFactor;
        statusBar.scaleFactor = scaleFactor;
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...") }
            Action { text: qsTr("&Save") }
            Action { text: qsTr("Save &As...") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                onTriggered:{
                    aboutPopup.open();
                }
            }
        }
    }
    Dialog {
        id: aboutPopup
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        ColumnLayout{
            anchors.fill: parent
            Item{
                width: image.width
                height: image.height
                Layout.alignment: Qt.AlignHCenter
                Image {
                    id: image
                    source: "qrc:/assets/logo.png"
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
                Material.accent: Material.primary
                Layout.alignment: Qt.AlignHCenter
                textFormat: Label.RichText
                selectByMouse: true
                readOnly: true
                text: "<style>a:link { color: " + Material.foreground + "; text-decoration: none;}</style><html>
<h1>Papercards</h1>
<p><small>Version 1.0</small></p>
<p>This project is open source and<br/>contributions are welcomed.</p>
<p>Visit <a href=\"https://github.com/Foxei/Papercards\">https://github.com/Foxei/<br/>Papercards</a> for more information, to report<br/>a bug or to suggest a new feature.</p>
<p><small>Copyright © 2019-2020 Simon Schäfer. All<br/>rights reserved.</small></p>
</html>"
                horizontalAlignment: Label.AlignHCenter
                onLinkActivated: Qt.openUrlExternally(link)
            }

        }
    }


    header: Components.EditorToolBar{
        id: toolBar
    }

    footer: Components.EditorStatusBar{
        id: statusBar
        onScaleFactorChanged: {
            root.scaleFactor = statusBar.scaleFactor
        }
    }

    Components.DualCardView {
        id: cardView
        anchors.fill: parent
    }
}
