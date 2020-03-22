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
    signal textBackground(color highlightColor)
    signal textForground(color textColor)

    signal newCard()
    signal newDeck()

    RowLayout {
        Components.MaterialToolButton {
            text: MD.icons.library_add
            ToolTip.text: "New deck"
            onClicked: toolBar.newDeck()
        }
        Components.MaterialToolButton {
            text: MD.icons.post_add
            ToolTip.text: "New card (" + newCard.nativeText + ")"
            onClicked: toolBar.newCard()
            Shortcut {
               id: newCard
               sequence: StandardKey.New
               onActivated: toolBar.newCard()
            }
        }
        ToolSeparator {}
        Components.MaterialToolButton {
            text: MD.icons.format_bold
            ToolTip.text: "Bold (" + bold.nativeText + ")"
            onClicked: toolBar.bold()
            Shortcut {
               id: bold
               sequence: StandardKey.Bold
               onActivated: toolBar.bold()
            }
        }

        Components.MaterialToolButton {
            text: MD.icons.format_italic
            ToolTip.text: "Italic (" + italic.nativeText + ")"
            onClicked: toolBar.italic()
            Shortcut {
               id: italic
               sequence: StandardKey.Italic
               onActivated: toolBar.italic()
            }
        }
        Components.MaterialToolButton {
            text: MD.icons.format_underlined
            ToolTip.text: "Underline (" + underlined.nativeText + ")"
            onClicked: toolBar.underlined()
            Shortcut {
               id: underlined
               sequence: StandardKey.Underline
               onActivated: toolBar.underlined()
            }
        }
        ToolSeparator {}
        Components.MaterialToolButton {
            text: MD.icons.format_color_text
            ToolTip.text: "Text color"
            onClicked: colorPicker.opened ? colorPicker.close() : colorPicker.open()

            Components.ColorPicker{
                id: colorPicker
                onAccepted: textForground(colorPicker.selectedColor)
            }
        }
        Components.MaterialToolButton {
            text: MD.icons.highlight
            ToolTip.text: "Highlight"
            onClicked: highlightPicker.opened ? highlightPicker.close() : highlightPicker.open()

            Components.ColorPicker{
                id: highlightPicker
                onAccepted: textBackground(highlightPicker.selectedColor)
            }
        }
        ToolSeparator {}
        Components.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_list_bulleted
            ToolTip.text: "Bullet list (" + bulletList.nativeText + ")"
            onClicked: toolBar.bulletList()
            Shortcut {
               id: bulletList
               sequence: "Ctrl+Shift+L"
               onActivated: toolBar.bulletList()
            }
        }
        Components.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_indent_increase
            ToolTip.text: "Increase list indention (" + increaseIndentation.nativeText + ")"
            onClicked: toolBar.increaseIndentation()
            Shortcut {
               id: increaseIndentation
               sequence: "Tab"
               onActivated: toolBar.increaseIndentation()
            }
        }

        Components.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_indent_decrease
            ToolTip.text: "Decrease list indention (" + decreaseIndentation.nativeText + ")"
            onClicked: toolBar.decreaseIndentation()
            Shortcut {
               id: decreaseIndentation
               sequence: "Shift+Tab"
               onActivated: toolBar.decreaseIndentation()
            }
        }
    }
}
