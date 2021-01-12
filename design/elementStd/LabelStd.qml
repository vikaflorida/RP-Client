import QtQuick 2.9
import QtQuick.Layouts 1.3

//  Элемент лейбла
Item{
    id: label
    implicitWidth:              labelStd.implicitWidth
    implicitHeight:             labelStd.implicitHeight
    property alias text:        labelStd.text
    property alias textColor:   labelStd.color
    property alias clip:        labelStd.clip
    property alias wrapMode:    labelStd.wrapMode
    Text {
        id: labelStd
        leftPadding: 0
        clip: true
        wrapMode: Text.WordWrap
    }
}
