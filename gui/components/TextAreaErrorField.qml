import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

TextArea {

    function showTopErrorMessage(showMessage){
        topErrorMessage.fade(showMessage);
    }
    function showBottomErrorMessage(showMessage, errorMessage){
        bottomErrorMessage.text = errorMessage
        bottomErrorMessage.visible = showMessage;

        Material.accent = (showMessage) ? "#B00020" : parent.Material.accent;
    }
    function updateCursorPosition(){
        select(cursorPosition-1,cursorPosition);
        deselect();
    }

    ErrorMessage{
        id: topErrorMessage
    }

    Label {
        id: bottomErrorMessage
        visible: false
        font.pointSize: 12
        anchors.bottomMargin: -10
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        z: 200
        Material.foreground: "#B00020"
    }
}
