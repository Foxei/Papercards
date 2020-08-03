import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

MenuBar {
    signal newDeck()
    signal openDeck()
    signal saveDeck()
    signal saveDeckAs()
    signal exportAsPdf()
    signal quitApplication()
    signal aboutApplication()

    Menu {
        title: qsTr("&File")
        Action {
            text: qsTr("&New...")
            onTriggered: newDeck()
        }
        Action {
            text: qsTr("&Open...")
            shortcut: StandardKey.Open
            onTriggered: openDeck()
        }
        Action {
            text: qsTr("&Save")
            onTriggered: saveDeck()
        }
        Action {
            text: "Save &As..."
            shortcut: StandardKey.SaveAs
            onTriggered: saveDeckAs()
        }
        MenuSeparator { }
        Action {
            text: "&Export As..."
            shortcut: StandardKey.Print
            onTriggered: exportAsPdf()
        }
        MenuSeparator { }
        Action {
            text: qsTr("&Quit")
            onTriggered: quitApplication()
        }
    }
    Menu {
        title: qsTr("&Help")
        Action {
            text: qsTr("&About")
            onTriggered: aboutApplication()
        }
    }
}
