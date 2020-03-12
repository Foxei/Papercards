import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12
import io.papercards.backend 1.0

ToolBar{

    Component.onCompleted: BackEnd.onComplete()

    RowLayout {
        spacing: 0

        ToolButton {
            icon.source: "qrc:/assets/format_bold.png"
            padding: 0
            spacing: 0
        }
        ToolButton {
            icon.source: "qrc:/assets/format_italic.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/format_underlined.png"
        }
        ToolSeparator {}
        ToolButton {
            icon.source: "qrc:/assets/color_lens.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/highlight.png"
        }
        ToolSeparator {}
        ToolButton {
            icon.source: "qrc:/assets/format_list_bulleted.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/format_indent_increase.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/format_indent_decrease.png"
        }
    }
}
