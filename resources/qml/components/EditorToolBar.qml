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
            icon.source: "qrc:/assets/new_deck.png"
            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            ToolTip.text: "<html><h1>Creates a new deck of flashcards.</h1> <p>With this you can create a new stack of flashcards. In order to avoid losing files and to have an optimal overview of your flashcards you should create a new stack for each topic.</p> </html>"
        }
        ToolButton {
            icon.source: "qrc:/assets/add_card.png"

            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            ToolTip.text: "<html><h1>Adds a new flashcards.</h1> <p>This allows you to add a new flashcard to the end of the current deck. You should create a new card for each question to get the best learning and printing results.</p> </html>"
        }
        ToolSeparator {}
        ToolButton {
            icon.source: "qrc:/assets/format_bold.png"
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
