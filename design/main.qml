import QtQml 2.2
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "appcolors.js" as Colors

Window {
    id: appWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("RP Client" + rpClient.errorString )
    minimumWidth:  640
    minimumHeight:  640
    color: Colors.backgroundColor
    property bool startSetConnectionAndInitial: false
    onStartSetConnectionAndInitialChanged: rpClient.startSetConnectionAndInitial = startSetConnectionAndInitial

    RPClient{
        id: rpClient
        anchors.fill: parent
        showTelemetryField: true
    }

    function debounce(func, ms){
        var callNow = !debounceTimer.running;
        debounceTimer.interval = ms;
        debounceTimer.running = true;
        if (callNow)
            func()
    }

    function throttle (callback, timer) {
        if (timer.running === false) {
            callback()
            timer.running = true
        }
    }

    function throttleArg (callback, timer, argum) {
        if (timer.running === false) {
            callback(argum)
            timer.running = true
        }
    }

    Timer{
        id: debounceTimer
        repeat: false
        running: false
        onTriggered:running = false
    }

    Timer{
        id: throttleTimer
        interval: 50
        repeat: false
        running: false
        onTriggered:running = false
    }
}
