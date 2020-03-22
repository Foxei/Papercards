import QtQuick 2.14
import Qt.labs.platform 1.0

/*MenuBar {
    signal newDeck()
    signal openDeck()
    signal saveDeck()
    signal saveDeckAs()
    signal quitApplication()
    signal aboutApplication()

    Menu {
        title: qsTr("&File")
        MenuItem {
            text: qsTr("&Open")
        }
        MenuItem {
            text: qsTr("&New")
        }

        MenuItem {
            text: "about.*"
        }

        MenuItem {
            text: qsTr("E&xit")
        }
    }
}*/

MenuBar {
    signal newDeck()
    signal openDeck()
    signal saveDeck()
    signal saveDeckAs()
    signal quitApplication()
    signal aboutApplication()
    //focus: true
    Menu {
        title: qsTr("File")
        MenuItem {
            text: qsTr("New...")
            onTriggered: newDeck()
        }
        MenuItem {
            text: qsTr("&Open...")
            shortcut: StandardKey.Open
            onTriggered: openDeck()
        }
        MenuItem {
            text: qsTr("&Save")
            shortcut: StandardKey.Save
            onTriggered: saveDeck()
        }
        MenuItem {
            text: "Save &As..."
            shortcut: StandardKey.SaveAs
            onTriggered: saveDeckAs()
        }
        MenuItem {
            text: qsTr("&Quit")
            onTriggered: quitApplication()
        }
    }
    Menu {
        title: qsTr("&Help")
        MenuItem {
            text: qsTr("&About")
            onTriggered: aboutApplication()
        }
    }
}
