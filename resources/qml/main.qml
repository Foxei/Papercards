import QtQuick 2.6
import QtQuick.Controls 2.2
import io.papercards.backend 1.0
import QtQuick.Controls.Material 2.2

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
