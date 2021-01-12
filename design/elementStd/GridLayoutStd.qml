import QtQuick 2.9
import QtQuick.Layouts 1.3

//  Элемент слоя-сетки
GridLayout {
    id: gridLayoutStd
    anchors.fill: parent
    columnSpacing: 2
    rowSpacing: 2
    anchors.margins: 0
    property double colMulti: gridLayoutStd.width / gridLayoutStd.columns
    property double rowMulti: gridLayoutStd.height / gridLayoutStd.rows
    function prefWidth (item) {
        return colMulti * item.Layout.columnSpan
    }
    function prefHeight (item) {
        return rowMulti * item.Layout.rowSpan
    }
}
