import QtQuick 2.0

//  Элемент ввода времени
Item {
    implicitWidth: textInputTime.implicitWidth
    implicitHeight: textInputTime.implicitHeight
    property alias textInputWidth:  textInputTime.textInputWidth
    property alias textInputHeight:  textInputTime.textInputHeight
    property alias label:           textInputTime.label     //  Лейбл
    property alias currentTime:     textInputTime.text      //  Текущее время

    property alias direction: textInputTime.direction       //  Формат отображения лейбла и области (вертикально, горизонтально)

    property color borderColorTimeOK:     "lightgrey"
    property color borderColorTimeNotOK:   "red"
    property string fillChar:   "-"

    property var hms: ["hh", "mm", "ss"]                    //  Формат отображения времени
    property bool timeOK: true                              //  Корректность времени
    property bool check23_59_59: false                      //  Управление проверкой времени
    property alias readOnly: textInputTime.readOnly         //  Флаг режима редактирования

    signal accept()

    onHmsChanged: {
        var i, j
        var separator = ";"
        var mask = ""
        for (i = 0; i < hms.length; i++)
        {
            if ((i+1) < hms.length)
            {
                if (hms[i+1].indexOf("z") >= 0)
                    separator = "."
                else
                    separator = ":"
            }
            else
                separator = ";"

            if  (hms[i])
            for (j = 0; j < hms[i].length; j++)
                mask = mask + "0"
            mask = mask + separator
        }
        if (i === 0) mask = separator
        mask = mask + fillChar
        textInputTime.inputMask = mask
    }

    TextInputStd{
        id: textInputTime
        readOnly: true
        direction: "V"
        label.text: "Time: "
        inputMask: if (hms.length !== 0)
                       ("00:00:00:" + fillChar)
        textInputBorder.color: timeOK ? borderColorTimeOK : borderColorTimeNotOK

        onTextInputChanged: if (check23_59_59) checkInputTime()
        onAcceptText: accept()

    }

    function checkInputTime(){
        var ch
        var timeString = "", hoursString = "", minutesString = "", secondsString = ""
        var hours, minutes, seconds
        var i
        for (i = 0; i < textInputTime.currentTextInput.length; i++) {
            ch = textInputTime.currentTextInput.slice(i,i+1)
            if (ch === ":") break;
            timeString +=ch
        }
        if (timeString.length > 2) {
            hours = parseInt(textInputTime.currentTextInput.slice(0,2))
            minutes = parseInt(textInputTime.currentTextInput.slice(2,4))
            seconds = parseInt(textInputTime.currentTextInput.slice(4,6))
        }
        else{
            i =0
            for (var position = 1; position <= 3; position ++) {
                timeString = ""
                for (i ; i < position*3; i++) {
                    ch = textInputTime.currentTextInput.slice(i,i+1)
                    if ((ch === ":") ||  (ch ==="")) {
                        i++;
                        if (timeString === "")
                            timeString = "0";
                        switch (position){
                        case 1:
                            hours = parseInt(timeString)
                            break;
                        case 2:
                            minutes = parseInt(timeString)
                            break;
                        case 3:
                            seconds = parseInt(timeString)
                            break;
                        }
                        break;
                    }
                    timeString +=ch
                }
            }
        }

        if ((hours <= 23) && (minutes <= 59) && (seconds <= 59)) {
            timeOK  = true
        }
        else {
            timeOK = false
        }

    }

    function getCurrentTime(){
        var format = ""
        var i, j
        for (i = 0; i < hms.length; i++)
        {
            for (j = 0; j < hms[i].length; j++)
                format = format + hms[i].charAt(j)
        }
        return Qt.formatTime(new Date(), format)
    }

    function setCurrentTime(){
        timeOK = true;
        currentTime = getCurrentTime();
    }

}

