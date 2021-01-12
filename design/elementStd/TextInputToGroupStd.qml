import QtQuick 2.0
import QtQuick.Layouts 1.3

TextInputStd {
    property variant location: []
    property var grid: location [0]
    Layout.row: location [1]
    Layout.column: location [2]
    Layout.rowSpan: location [3]
    Layout.columnSpan: location [4]
    property int preferredHeight: grid.prefHeight(this)
    property int preferredWidth: grid.prefWidth(this)
    Layout.preferredHeight: preferredHeight
    Layout.preferredWidth:  preferredWidth

    property int stdPrefHeight: grid.prefHeight(this)
}
