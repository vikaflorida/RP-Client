import QtQuick 2.0
import "appcolors.js" as Colors

//  Общий элемент
Item {
    id : rpClient
    readonly property int durationAnimation: 150
    property bool netState: false                       //  Состояние сети (подключение к аппаратуре)
    property string errorString: ""
    property bool startSetConnectionAndInitial: false   //  Строка ошибки
    onStartSetConnectionAndInitialChanged: setConnections()

    property bool showTelemetryField: false             //  Флаг отображения области телеметрии


    Modes   {
        id: modes
        durationAnimation: parent.durationAnimation
        anchors.left: parent.left
        width: parent.width * 1/3

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.margins: 10
        objectName: "modes"
        enabledHalfSets: netState
    }

    Telemetry   {
        id: tele
        anchors.left: modes.right
        anchors.right: parent.right

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.margins: 10
        objectName: "tele"
        enabled: netState
        show: showTelemetryField
    }

    function updateNetState()
    {
        netState = backFrontBridge.connected
        if (!netState)
        {
            backFrontBridge.tryConnect()
        }
        else errorString = ""
    }

    function updateTelemetry()
    {
        modes.telemetry = backFrontBridge.telemetry
        tele.telemetry = backFrontBridge.telemetry
    }

    function updateErrorString()
    {
        if (backFrontBridge.errorString === "") errorString =""
        else errorString = " (" + backFrontBridge.errorString + ")"
    }


    function updateOpMode()
    {
        modes.halfSetOpMode = backFrontBridge.halfSetOpMode
    }

    function setConnections()
    {
        backFrontBridge.connectedChanged.connect(updateNetState)
        backFrontBridge.telemetryChanged.connect(updateTelemetry)
        backFrontBridge.errorStringChanged.connect(updateErrorString)
        backFrontBridge.halfSetOpModeChanged.connect(updateOpMode)
        updateNetState()
    }

    Timer{
        id: netUpdater
        interval: 5000
        repeat: true
        running: true
        onTriggered:updateNetState()
    }
}
