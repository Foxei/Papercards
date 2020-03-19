import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "../basics/MaterialDesign.js" as MD
import "../basics/" as Basics

ToolBar{
    property bool enableTextFunctions: true;
    property bool enableEditorFunctions: true;

    FontLoader {
        id: iconFont
        source: "qrc:/assets/MaterialIcons-Regular.ttf"
    }

    RowLayout {
        Basics.MaterialToolButton {
            text: MD.icons.library_add
            ToolTip.text: "New deck"
        }
        Basics.MaterialToolButton {
            text: MD.icons.post_add
            ToolTip.text: "New card"
        }
        ToolSeparator {}
        Basics.MaterialToolButton {
            enabled: enableTextFunctions
            text: MD.icons.format_bold
            ToolTip.text: "Bold"
        }
        Basics.MaterialToolButton {
            enabled: enableTextFunctions
            text: MD.icons.format_italic
            ToolTip.text: "Italic"
        }
        Basics.MaterialToolButton {
            enabled: enableTextFunctions
            text: MD.icons.format_underlined
            ToolTip.text: "Underline"
        }
        ToolSeparator {}
        Basics.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_color_text
            ToolTip.text: "Text color"
        }
        Basics.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.highlight
            ToolTip.text: "Highlight"
        }
        ToolSeparator {}
        Basics.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_list_bulleted
            ToolTip.text: "Bullet list"
        }
        Basics.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_indent_increase
            ToolTip.text: "Increase list indention"
        }
        Basics.MaterialToolButton {
            enabled: enableEditorFunctions
            text: MD.icons.format_indent_decrease
            ToolTip.text: "Decrease list indention"
        }
    }
}
