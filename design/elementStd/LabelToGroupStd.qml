import QtQuick 2.0
import QtQuick.Layouts 1.3

LabelStd {
    property var location
    property var grid: location !== undefined ? location [0] : 0
    Layout.row:  location !== undefined ? location [1] : 0
    Layout.column: location !== undefined ? location [2] : 0
    Layout.rowSpan: location !== undefined ? location [3] : 0
    Layout.columnSpan: location !== undefined ? location [4] : 0
    property int preferredHeight: location !== undefined ? grid.prefHeight(this) : 0
    property int preferredWidth: location !== undefined ? grid.prefWidth(this) : 0
    Layout.preferredHeight: location !== undefined ? preferredHeight : 0
    Layout.preferredWidth:  location !== undefined ? preferredWidth : 0
}
