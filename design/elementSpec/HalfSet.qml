import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as QQC1
import "../elementStd" as ESTD
import "../appcolors.js" as Colors

//  Элемент полукомплекта аппаратуры
Item {
    id: halfSet
    property string labelText               //  Название переключателя
    property int durationAnimation : 0      //  Длительность анимации
    implicitHeight: switchStd.height
    implicitWidth: label.implicitWidth + switchStd.width + 20

    property bool frost: false              //  Заморозка элемента
    property alias checked: switchStd.checked
    signal switchClicked(var halfSet)
    property bool acceptOn: true
    property bool acceptOff: true


    //  Установить режим отображения оперативного режима для переключателя
    function setOpModeSwitchActiveColor()
    {
        switchStd.handleActiveColor             =   Colors.switchHandleOpModeColor
        switchStd.handleEnteredActiveColor      =   Colors.switchHandleEnteredOpModeColor
        switchStd.pressedActiveColor            =   Colors.switchPressedOpModeColor
        switchStd.borderActiveColor             =   Colors.switchBorderOpModeColor
    }

    //  Установить режим отображения режима оп умолчанию для переключателя
    function setDefaultSwitchActiveColor()
    {
        switchStd.handleActiveColor             =   Colors.switchHandleActiveColor
        switchStd.handleEnteredActiveColor      =   Colors.switchHandleEnteredActiveColor
        switchStd.pressedActiveColor            =   Colors.switchPressedActiveColor
        switchStd.borderActiveColor             =   Colors.switchBorderActiveColor
    }

    ESTD.LabelStd{
        id: label
        text: labelText
        textColor: Colors.textColor
        anchors.verticalCenter: parent.verticalCenter
    }

    ESTD.SwitchStd{
        id: switchStd
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        grooveNonActiveColor: Colors.switchGrooveNonActiveColor
        grooveActiveColor: Colors.switchGrooveActiveColor

        handleNonActiveColor: Colors.switchHandleNonActiveColor
        handleActiveColor: Colors.switchHandleActiveColor
        handleEnteredNonActiveColor: Colors.switchHandleEnteredNonActiveColor
        handleEnteredActiveColor: Colors.switchHandleEnteredActiveColor

        pressedNonActiveColor: Colors.switchPressedNonActiveColor
        pressedActiveColor: Colors.switchPressedActiveColor

        borderActiveColor: Colors.switchBorderActiveColor
        borderNonActiveColor: Colors.switchBorderNonActiveColor

        durationAnimation: halfSet.durationAnimation
        radius: 4
        enabled: !halfSet.frost

        onClicked: halfSet.switchClicked(halfSet)
    }

    states: [
        State{
            name: "nonEnabled"
            when: ((!enabled) && (!frost))
            PropertyChanges {
                target: halfSet
                opacity: 0.5
            }
        },
        State{
            name: "nonAcceptOn"
            when: !acceptOn
            PropertyChanges {
                target: switchStd
                borderActiveColor: borderNonActiveColor
            }
        },
        State{
            name: "nonAcceptOff"
            when: !acceptOff
            PropertyChanges {
                target: switchStd
                borderNonActiveColor: borderActiveColor
            }
        }
    ]

    Behavior on opacity {
        NumberAnimation {
            duration: durationAnimation
        }
    }
}
