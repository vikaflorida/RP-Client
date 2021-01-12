import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as QQC1
import "./elementStd" as ESTD
import "./elementSpec" as ESPEC
import "appcolors.js" as Colors


//  Элемент отображения режимов работы
Item {
    id: modes
    implicitHeight: kit11.implicitHeight + kit12.implicitHeight +
                    kit21.implicitHeight + kit22.implicitHeight +
                    kitV.implicitHeight + buttonAllOff.implicitHeight +
                    runningTime.implicitHeight
    implicitWidth: buttonAllOff.implicitWidth
    property int durationAnimation
    property var telemetry
    property var halfSetOpMode
    property bool enabledHalfSets: false


    Rectangle{
        enabled: enabledHalfSets
        color: Colors.transparent
        implicitHeight: parent.implicitHeight
        implicitWidth: parent.implicitWidth
        anchors.fill: parent
        property var halfSetChecked: (kit11.checked || kit12.checked || kit21.checked || kit22.checked)
        onHalfSetCheckedChanged: {
            if (halfSetChecked) timer.start()
            else timer.stop()
        }
        onEnabledChanged: if ((enabled) && (halfSetChecked) && (!(timer.running))) timer.start()
                          else if (!(enabled)) timer.frost()

        ColumnLayout{
            id: columnHalfSet
            spacing: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 20
            property bool checked: false


            ESPEC.HalfSet{
                id: kit11
                labelText: "Kit 1.1"
                durationAnimation: modes.durationAnimation
                enabled: modes.enabledHalfSets
                frost: modes.frost
                onSwitchClicked: {
                    if (checked)
                        backFrontBridge.setCommand("KIT1_HalfSet_1_ON")
                    else
                        backFrontBridge.setCommand("KIT1_HalfSet_1_OFF")
                }
                onCheckedChanged: if (kit11.checked)kit11Timer.start()
                                  else {kit11Timer.stop(); setKit1DefaultMode(kit11)}
            }

            ESPEC.HalfSet{
                id: kit12
                labelText: "Kit 1.2"
                durationAnimation: modes.durationAnimation
                enabled: modes.enabledHalfSets
                frost: modes.frost
                onSwitchClicked: {
                    if(checked)
                        backFrontBridge.setCommand("KIT1_HalfSet_2_ON")
                    else
                        backFrontBridge.setCommand("KIT1_HalfSet_2_OFF")
                }

                onCheckedChanged: if (kit12.checked)kit12Timer.start()
                                  else {kit12Timer.stop(); setKit1DefaultMode(kit12)}
            }

            ESPEC.HalfSet{
                id: kit21
                labelText: "Kit 2.1"
                durationAnimation: modes.durationAnimation
                enabled: modes.enabledHalfSets
                frost: modes.frost
                onSwitchClicked: {
                    if(checked)
                        backFrontBridge.setCommand("KIT2_HalfSet_1_ON")
                    else
                        backFrontBridge.setCommand("KIT2_HalfSet_1_OFF")
                }
            }

            ESPEC.HalfSet{
                id: kit22
                labelText: "Kit 2.2"
                durationAnimation: modes.durationAnimation
                enabled: modes.enabledHalfSets
                frost: modes.frost
                onSwitchClicked: {
                    if(checked)
                        backFrontBridge.setCommand("KIT2_HalfSet_2_ON")
                    else
                        backFrontBridge.setCommand("KIT2_HalfSet_2_OFF")
                }
            }

            ESPEC.KitV{
                id: kitV
                heightStatusIndicator: 30
                enabled: modes.enabledHalfSets
                onActiveChanged: if (active) kitVTimer.start()
                                 else{kitVTimer.stop(); kitV.setDefaultMode()}
            }
        }
        ESTD.ButtonStd{
            id: buttonAllOff
            anchors.top: columnHalfSet.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Отключить всё"
            color: Colors.buttonColor
            pressedColor: Colors.buttonPressedColor
            nonEnabledColor: Colors.buttonNonEnabledColor
            enabled: modes.enabledHalfSets
            onClicked: {
                if (!modes.frost)
                {
                    kit11.checked = false
                    kit12.checked = false
                    kit21.checked = false
                    kit22.checked = false
                    backFrontBridge.setCommand("KIT1_KIT2_OFF")
                }
            }
        }

        ESPEC.RunningTimeCounter
        {
            id: runningTime
            anchors.top: buttonAllOff.bottom
            anchors.left: buttonAllOff.left
            enabled:  modes.enabledHalfSets
        }

        ESPEC.TextInputTimer
        {
            id: timer
            anchors.top: runningTime.bottom
            anchors.topMargin: 20
            anchors.left: buttonAllOff.left
            label.text: "Секундомер (МИН:СЕК)"
            label.textColor: Colors.textColor
            textInputHeight: 26
            textInputWidth: 60
            enabled:  modes.enabledHalfSets
        }
    }

    onTelemetryChanged: {

        frost = false;
        if (lastSwitch !== null){
            if (lastSwitch.checked)
                lastSwitch.acceptOn = true
            else if (!lastSwitch.checked)
                lastSwitch.acceptOff = true
        }
        for (var prop in telemetry) {
            if (prop.indexOf("Kit2_1_ON") >= 0) {
                if (telemetry[prop] === "true") kit21.checked = true;
                else kit21.checked = false;
            }
            else if (prop.indexOf("Kit2_2_ON") >= 0) {
                if (telemetry[prop] === "true") kit22.checked = true;
                else kit22.checked = false;
            }
            else if (prop.indexOf("Kit1_1_ON") >= 0) {
                if (telemetry[prop] === "true") kit11.checked = true;
                else kit11.checked = false;
            }
            else if (prop.indexOf("Kit1_2_ON") >= 0) {
                if (telemetry[prop] === "true") kit12.checked = true;
                else kit12.checked = false;
            }
            else if (prop.indexOf("KitV_ON") >= 0) {
                if (telemetry[prop] === "true") kitV.active = true;
                else kitV.active = false;
            }
            else if (prop.indexOf("Hourse_TIME") >= 0) {
                runningTime.currentTime = telemetry[prop] + runningTime.currentTime.substring(runningTime.currentTime.indexOf(":"), runningTime.currentTime.length)
            }
            else if (prop.indexOf("Minutes_TIME") >= 0) {
                var tmp = telemetry[prop]
                if (telemetry[prop].length === 1) tmp = "0" +  telemetry[prop]
                runningTime.currentTime = runningTime.currentTime.substring(0, (runningTime.currentTime.indexOf(":")+1)) + tmp
            }
        }
    }

    onHalfSetOpModeChanged: {
        for (var prop in halfSetOpMode)
        {
            if (prop.indexOf("Kit2_1") >= 0)
            {
                if (halfSetOpMode[prop])  kit21.setOpModeSwitchActiveColor()
                else kit21.setDefaultSwitchActiveColor()
            }
            else if (prop.indexOf("Kit2_2") >= 0)
            {
                if (halfSetOpMode[prop]) kit22.setOpModeSwitchActiveColor()
                else kit22.setDefaultSwitchActiveColor()
            }
        }
    }

    function setKit1DefaultMode(kit)
    {
        if (!kit.checked) kit.setDefaultSwitchActiveColor()
    }

    function setKit1OpMode(kit)
    {
        if (kit.checked) kit.setOpModeSwitchActiveColor()
    }

    property int someSwitchClickCount: 0
    Component.onCompleted:
    {
        kit11.onSwitchClicked.connect(switchChanged)
        kit12.onSwitchClicked.connect(switchChanged)
        kit21.onSwitchClicked.connect(switchChanged)
        kit22.onSwitchClicked.connect(switchChanged)
    }
    property bool frost: false
    property var lastSwitch: null
    function switchChanged(sender)
    {
         frost = true;
        lastSwitch = sender
        if (lastSwitch.checked)
            lastSwitch.acceptOn = false
        else if (!lastSwitch.checked)
            lastSwitch.acceptOff = false
    }

    Timer{
        id: kit11Timer
        interval: 60000
        repeat: false
        running: false
        onTriggered: setKit1OpMode(kit11)
    }
    Timer{
        id: kit12Timer
        interval: 60000
        repeat: false
        running: false
        onTriggered: setKit1OpMode(kit12)
    }
    Timer{
        id: kitVTimer
        interval: 1000
        repeat: false
        running: false
        onTriggered: kitV.setOpMode()
    }

}

