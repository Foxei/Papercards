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
            Icon {
                iconSource: "qrc:/assets/new_deck.png"
            }

            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            ToolTip.text: "<html><h1>Creates a new deck of flashcards.</h1> <p>With this you can create a new stack of flashcards. In order to avoid losing files and to have an optimal overview of your flashcards you should create a new stack for each topic.</p> </html>"
        }
        ToolButton {
            Icon {
                iconSource: "qrc:/assets/add_card.png"
            }
            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            ToolTip.text: "<html><h1>Adds a new flashcards.</h1> <p>This allows you to add a new flashcard to the end of the current deck. You should create a new card for each question to get the best learning and printing results.</p> </html>"
        }
        ToolSeparator {}
        ToolButton {
            enabled: enableTextFunctions
            Icon {
                iconSource: "qrc:/assets/format_bold.png"
            }
        }
        ToolButton {
            enabled: enableTextFunctions
            Icon {
                iconSource: "qrc:/assets/format_italic.png"
            }
        }
        ToolButton {
            enabled: enableTextFunctions
            Icon {
                iconSource: "qrc:/assets/format_underlined.png"
            }
        }
        ToolSeparator {}
        ToolButton {
            enabled: enableEditorFunctions
            Icon {
                iconSource: "qrc:/assets/color_lens.png"
            }
        }
        ToolButton {
            enabled: enableEditorFunctions
            Icon {
                iconSource: "qrc:/assets/highlight.png"
            }
        }
        ToolSeparator {}
        ToolButton {
            enabled: enableEditorFunctions
            Icon {
                iconSource: "qrc:/assets/format_list_bulleted.png"
            }
        }
        ToolButton {
            enabled: enableEditorFunctions
            Icon {
                iconSource: "qrc:/assets/format_indent_increase.png"
            }
        }
        ToolButton {
            enabled: enableEditorFunctions
            Icon {
                iconSource: "qrc:/assets/format_indent_decrease.png"
            }
        }
    }
}
