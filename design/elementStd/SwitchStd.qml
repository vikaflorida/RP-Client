import QtQuick 2.9
import QtQuick.Controls 1.4 as QQC1
import QtQuick.Controls.Styles 1.4

//  Элемент свитча (переключателя)
Item{
    id: switchStd

    height: 48
    width: 92

    // Определение цветов дорожки переключателя
    property color grooveNonActiveColor: "dimgray"
    property color grooveActiveColor: "black"
    property color grooveEnteredNonActiveColor: grooveNonActiveColor
    property color grooveEnteredActiveColor: grooveActiveColor

    // Определение цветов ручки переключателя
    property color handleNonActiveColor: "gray"
    property color handleActiveColor: "yellow"
    property color handleEnteredNonActiveColor: handleNonActiveColor
    property color handleEnteredActiveColor: handleEnteredNonActiveColor

    // Определение основных цветов переключателя
    property color pressedNonActiveColor: handleNonActiveColor
    property color pressedActiveColor: handleActiveColor
    // Определение цветов бордера переключателя
    property color borderNonActiveColor: "transparent"
    property color borderActiveColor: handleActiveColor

    property int durationAnimation: 100     // Длительность анимации
    property int borderWidth: 4
    property int radius: height/2

    property alias checked: switchComponent.checked

    signal clicked()

    Rectangle{
        id: borderSwitch

        Behavior on color {
            ColorAnimation {
                duration: switchStd.durationAnimation
            }
        }
        anchors.fill: parent

        radius: switchStd.radius

        color: { switchComponent.checked ? switchStd.borderActiveColor :  switchStd.borderNonActiveColor}

        QQC1.Switch {
            id: switchComponent
            anchors.centerIn: parent
            height: parent.height - switchStd.borderWidth
            width: parent.width - switchStd.borderWidth

            style: SwitchStyle {
                groove: Rectangle {
                    id: grooveRect
                    height: switchComponent.height
                    width: switchComponent.width
                    color: {switchComponent.checked ? switchStd.grooveActiveColor : switchStd.grooveNonActiveColor}
                    Behavior on color {
                        ColorAnimation {
                            duration: switchStd.durationAnimation
                        }
                    }
                    radius: switchStd.radius
                }
                handle: Rectangle {
                    id: handleRect
                    anchors.centerIn: parent
                    width: switchStd.height - 10
                    height: switchStd.height - 10
                    border.width: 4
                    border.color: switchComponent.checked ?  switchStd.grooveActiveColor : switchStd.grooveNonActiveColor
                    radius: switchStd.radius
                    Behavior on color {
                        ColorAnimation {
                            duration: switchStd.durationAnimation
                        }
                    }
                    Behavior on border.color {
                        ColorAnimation {
                            duration: switchStd.durationAnimation
                        }
                    }
                    MouseArea{
                        id: mouseArea
                        property bool mouseAreaEnterned: false
                        anchors.fill: parent
                        propagateComposedEvents: true
                        hoverEnabled: true
                        onEntered: mouseAreaEnterned = true
                        onExited: mouseAreaEnterned = false
                        states:[
                            State{
                                name: "enteredMouse"
                                when: mouseArea.mouseAreaEnterned
                                PropertyChanges {
                                    target: handleRect
                                    color: switchComponent.checked ? switchStd.handleEnteredActiveColor : switchStd.handleEnteredNonActiveColor
                                }
                            }
                        ]
                    }
                    states:[
                        State{
                            name: "pressed"
                            when: switchComponent.pressed
                            PropertyChanges {
                                target: handleRect
                                color : switchComponent.checked ? switchStd.pressedActiveColor : switchStd.pressedNonActiveColor
                            }
                        },
                        State{
                            name: "nonPressed"
                            when: !switchComponent.pressed
                            PropertyChanges {
                                target: handleRect
                                color: switchComponent.checked ? switchStd.handleActiveColor : switchStd.handleNonActiveColor
                            }
                        }
                    ]
                }
            }

            onClicked: switchStd.clicked()
        }
    }
}
