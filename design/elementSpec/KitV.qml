import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../elementStd" as ESTD
import "../appcolors.js" as Colors

//  Элемент V аппаратуры
Item {
    id: kitV
    property alias heightStatusIndicator: kitVSI.implicitHeight
    implicitHeight: row.implicitHeight
    implicitWidth: row.implicitWidth
    property int durationAnimation : 0      //  Длительность анимации
    property alias active: kitVSI.active    //  Статус активности индикатора

    function setOpMode()
    {
        kitVSI.onColor = Colors.statusIndicatorOppModeColor
    }
    function setDefaultMode()
    {
        kitVSI.onColor = Colors.statusIndicatorOnColor
    }

    RowLayout{
        id : row
        ESTD.LabelStd{
            text: "Kit V"
            textColor: Colors.textColor
            anchors.verticalCenter: parent.verticalCenter
        }
        ESTD.StatusIndicatorStd{
            id: kitVSI
            toolTipTextSI: "Kit V"
            durationAnimation:  kitV.durationAnimation
            implicitWidth: implicitHeight
            offColor: Colors.statusIndicatorOffColor
            onColor: Colors.statusIndicatorOnColor
        }
    }
    states: [
        State{
            name: "nonEnabled"
            when: !enabled
            PropertyChanges {
                target: kitV
                opacity: 0.5
            }
        }
    ]

    Behavior on opacity {
        NumberAnimation {
            duration: durationAnimation
        }
    }
}
