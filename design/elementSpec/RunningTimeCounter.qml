import QtQuick 2.0
import "../elementStd" as ESTD
import "../appcolors.js" as Colors

//  Элемент отображения времени наработки
ESTD.TextInputTimeStd
{
    id: runningTime
    anchors.topMargin: 20
    textInputWidth: 60
    textInputHeight: 26
    label.text: "Время н. (ЧАС:МИН): "
    label.textColor: Colors.textColor
    hms: []
    currentTime: ":"
    readOnly: true
}
