import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.12
import io.papercards.backend 1.0

ToolBar{

    Component.onCompleted: BackEnd.onComplete()

    RowLayout {
        spacing: 1
        ToolButton {
            icon.source: "qrc:/assets/clipboard.png"
        }
        ToolSeparator {}
        ComboBox {
            model: BackEnd.available_font_families
            displayText: currentIndex === -1 ? "Font Families..." : currentText
            Layout.preferredWidth: 250
        }
        ComboBox {
            model: BackEnd.default_font_sizes
            displayText: currentIndex === -1 ? "Font Sizes..." : currentText
            Layout.preferredWidth: 70
        }
        ToolSeparator {}
        ToolButton {
            icon.source: "qrc:/assets/font_bold.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/font_italic.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/font_underlined.png"
        }
        ToolSeparator {}
        ToolButton {
            icon.source: "qrc:/assets/font_color.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/highlighter.png"
        }
        ToolSeparator {}
        ToolButton {
            icon.source: "qrc:/assets/bullet.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/increase_indentation.png"
        }
        ToolButton {
            icon.source: "qrc:/assets/decrease_indentation.png"
        }
    }
}
