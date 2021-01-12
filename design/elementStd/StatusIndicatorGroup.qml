import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: siGroup
//    property int count
    property var toolTips: []

    property bool onSI
    property bool loading
    property color onColor
    property color loadingColor
    property int durationAnimation
    property int spacing
    color: "transparent"
    RowLayout{
        id: rowLayout
        spacing: siGroup.spacing
        anchors.fill: parent
        anchors.margins: 0
        Repeater{
            id:siRepeater
            model: toolTips
//            count: siGroup.count
            StatusIndicatorStd{
                id: si
                toolTipTextSI: modelData
                onColor: siGroup.onColor
                loadingColor: siGroup.loadingColor
                durationAnimation:  siGroup.durationAnimation
                implicitHeight: siGroup.height
                implicitWidth: rowLayout/3
                onWarningChanged:
                    if (warning) warningRect.color = "red"
                    else warningRect.color = "transparent"
            }
        }
    }


    Rectangle{
        id: warningRect
        height: 10
        width: 10
        anchors.left: rowLayout.right
        anchors.verticalCenter: rowLayout.verticalCenter
        anchors.leftMargin: 10
        radius: 5
        color: "transparent"
    }


    function getActiveStutusIndicatorGroup()
    {
        return siRepeater.itemAt(0).active
    }

    function getOnStutusIndicatorGroup()
    {
        return siRepeater.itemAt(0).onSI

    }

    function setOnItemAt(index, on){
            siRepeater.itemAt(index).onSI = on
    }

    function setOnAll(on){
        for (var i = 0; i < siRepeater.count; i++){
            siRepeater.itemAt(i).onSI = on
        }
    }

    function setActiveItemAt(index, active){
            siRepeater.itemAt(index).active = active
    }

    function setActiveAll(active){
        for (var i = 0; i < siRepeater.count; i++){
            siRepeater.itemAt(i).active = active
        }
    }
}
