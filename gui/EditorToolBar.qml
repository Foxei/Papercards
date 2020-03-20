import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "scripts/MaterialDesign.js" as MD
import "components" as Components

ToolBar{
    id: toolBar
    property bool enableTextFunctions: true;
    property bool enableEditorFunctions: true;

    signal bold()
    signal italic()
    signal underlined()
    signal bulletList()
    signal increaseIndentation()
    signal decreaseIndentation()

    RowLayout {
        Components.MaterialToolButton {
            text: MD.icons.library_add
            ToolTip.text: "New deck"
        }
        Components.MaterialToolButton {
            text: MD.icons.post_add
            ToolTip.text: "New card"
        }
        ToolSeparator {}
        Components.MaterialToolButton {
            text: MD.icons.format_bold
            ToolTip.text: "Bold"
            onClicked: toolBar.bold()
            focusPolicy: Qt.NoFocus
        }
        Components.MaterialToolButton {
            text: MD.icons.format_italic
            ToolTip.text: "Italic"
            onClicked: toolBar.italic()
            focusPolicy: Qt.NoFocus
        }
        Components.MaterialToolButton {
            text: MD.icons.format_underlined
            ToolTip.text: "Underlined"
            onClicked: toolBar.underlined()
            focusPolicy: Qt.NoFocus
        }
        ToolSeparator {}
        Components.MaterialToolButton {
            text: MD.icons.format_color_text
            ToolTip.text: "Text color"
        }
        Components.MaterialToolButton {
            text: MD.icons.highlight
            ToolTip.text: "Highlight"
        }
        ToolSeparator {}
        Components.MaterialToolButton {
            text: MD.icons.format_list_bulleted
            ToolTip.text: "Bullet list"
            onClicked: toolBar.bulletList()
            focusPolicy: Qt.NoFocus
        }
        Components.MaterialToolButton {
            text: MD.icons.format_indent_increase
            ToolTip.text: "Increase list indention"
            action: increaseIndentation
            focusPolicy: Qt.NoFocus
        }
        Action {
           id: increaseIndentation
           shortcut: "Tab"
           onTriggered: toolBar.increaseIndentation()
        }
        Components.MaterialToolButton {
            text: MD.icons.format_indent_decrease
            ToolTip.text: "Decrease list indention"
            action: decreaseIndentation
            focusPolicy: Qt.NoFocus
        }
        Action {
           id: decreaseIndentation
           shortcut: "Shift+Tab"
           onTriggered: toolBar.decreaseIndentation()
        }
    }
}
