import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtGraphicalEffects 1.0
import io.papercards.backend 1.0

ToolBar{
    property bool enableTextFunctions: true;
    property bool enableEditorFunctions: true;

    Component.onCompleted: BackEnd.onComplete()

    RowLayout {
        spacing: 0
        ToolButton {
            icon.source: "qrc:/assets/new_deck.png"

            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "New deck"
        }
        ToolButton {
            icon.source: "qrc:/assets/add_card.png"

            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "New card"
        }
        ToolSeparator {}
        ToolButton {
            enabled: enableTextFunctions
            icon.source: "qrc:/assets/format_bold.png"

            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Bold"
        }
        ToolButton {
            enabled: enableTextFunctions
            icon.source: "qrc:/assets/format_italic.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Italic"
        }
        ToolButton {
            enabled: enableTextFunctions
            icon.source: "qrc:/assets/format_underlined.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Underline"
        }
        ToolSeparator {}
        ToolButton {
            enabled: enableEditorFunctions
            icon.source: "qrc:/assets/color_lens.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Text color"
        }
        ToolButton {
            enabled: enableEditorFunctions
            icon.source: "qrc:/assets/highlight.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Highlight"
        }
        ToolSeparator {}
        ToolButton {
            enabled: enableEditorFunctions
            icon.source: "qrc:/assets/format_list_bulleted.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Bullet list"
        }
        ToolButton {
            enabled: enableEditorFunctions
            icon.source: "qrc:/assets/format_indent_increase.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Increase list indention"
        }
        ToolButton {
            enabled: enableEditorFunctions
            icon.source: "qrc:/assets/format_indent_decrease.png"
            ToolTip.delay: 200
            ToolTip.visible: hovered
            ToolTip.text: "Decrease list indention"
        }
    }
}
