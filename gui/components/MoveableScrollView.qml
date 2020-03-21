import QtQuick 2.14
import QtQuick.Controls 2.14

ScrollView {
    /**
     * @param type [Qt.Horizontal, Qt.Vertical]
     * @param ratio 1.0 to 1.0
     */
    function scrollTo(ratio) {
        ScrollBar.vertical.setPosition(ratio - ScrollBar.vertical.size)
    }
}
