import QtQuick 2.0
import "../elementStd" as ESTD

//  Элемент счетчика времени (таймера)
Item{
    implicitHeight:             textInputTime.implicitHeight
    implicitWidth:              textInputTime.implicitWidth
    property alias label:       textInputTime.label
    property alias direction:   textInputTime.direction      //  Порядок расположения подписи и тестовой области
    property alias textInputHeight:       textInputTime.textInputHeight
    property alias textInputWidth:   textInputTime.textInputWidth

    readonly property bool running: timer.running           //  Свойства проверки запущен ли таймер
    function start()
    {
        timer.start()
    }

    function frost()
    {
        timer.stop()
    }
    function stop()
    {
        timer.stop()
        timer.m = 0;
        timer.s = 0;
        timer.updateTime()
    }

    ESTD.TextInputTimeStd {
        id: textInputTime
        direction: "V"
        readOnly: true
        hms: ["mm", "ss"]
        currentTime: "00:00"
    }

    Timer{
        property int m: 0
        property int s: 0
        id: timer
        interval: 1000
        repeat: true
        running: false
        onTriggered:{
            increaseTime()
            updateTime()
        }
        function increaseTime()
        {
            if (s < 59){
                s++
            }
            else {
                s = 0
                m++
                if (m >= 59)
                    m = 0
            }
        }

        function updateTime()
        {
            var time = ""
            if (m < 10)
                time = "0" + m + ":"
            else
                time = m + ":"
            if (s < 10)
                time = time + "0" + s
            else
                time = time = time + s
            textInputTime.currentTime = time

        }
    }
}
