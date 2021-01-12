import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

//  Элемент кнопки
Button {
    id: buttonStd
    readonly property int stdImplicitWidth: 128     //  Стандартная ширина элемента
    readonly property int stdImplicitHeight: 44     //  Стандартная высота элемента
    property int durationAnimation: 50              //  Длительность анимации

    implicitWidth:  stdImplicitWidth
    implicitHeight: stdImplicitHeight

    ToolTip.visible: hovered
    ToolTip.delay: 1000
    ToolTip.timeout: 5000
    ToolTip.text: buttonStd.text

    property alias radius: background.radius
    property alias border: background.border
    property color color: "gray"                    //  Основной цвет
    property color pressedColor: "darkgray"         //  Цвет нажатия
    property color nonEnabledColor: "black"         //  Цвет "выключенной" кнопки


    background:

        Rectangle {
        id: background
        antialiasing: true
        radius: 2
        anchors.fill: parent
        anchors.margins: 0

        Behavior on color {
            ColorAnimation {
                duration: buttonStd.durationAnimation
            }
        }
        states: [
            State{
                name: "nonPressed"
                when: !pressed
                PropertyChanges {
                    target: background
                    color: buttonStd.color
                }
            },
            State{
                name: "pressed"
                when: pressed
                PropertyChanges {
                    target: background
                    color: buttonStd.pressedColor
                }
            }
        ]
    }
    states: [
        State{
            name: "nonPressed"
            when: !enabled
            PropertyChanges {
                target: background
                color: buttonStd.nonEnabledColor
            }
        }
    ]
}
