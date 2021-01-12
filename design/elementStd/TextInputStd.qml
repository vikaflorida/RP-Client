import QtQuick 2.9
import QtQuick.Layouts 1.3

// Элемен текстовой области для ввода
Rectangle {
    id: textInputStd
    property string direction: "H"  // "H"(слева лейбл, справа область) или "V" (вверху лейбл, внизу область)
    property int durationAnimation : 1000

    implicitWidth:
        if (direction === "H")
            (labelStd.implicitWidth + textField.implicitWidth)
        else
            textField.implicitWidth > labelStd.implicitWidth?
                        textField.implicitWidth : labelStd.implicitWidth
    implicitHeight:
        if (direction === "H")
            textField.implicitHeight > labelStd.implicitHeight?
                        textField.implicitHeight : labelStd.implicitHeight
        else  (labelStd.implicitHeight + textField.implicitHeight)


    property alias label:               labelStd                //  Элемент подписи

    property alias readOnly:            textInput.readOnly      //  Флаг разрешения редактирования текста
    property alias text:                textInput.text          //  Текст
    property alias currentTextInput:    textInput.text          //  Текущий текст
    property alias inputMask:           textInput.inputMask     //  Маска
    property alias textColor:           textInput.color         //  Цвет текста
    property alias objectName:          textInput.objectName    //  Объектное имя текста
    property alias coursorVisible:      textInput.cursorVisible //  Отображение курсора в области
    property alias wrapMode:            textInput.wrapMode
    property alias clip:                textInput.clip
    property alias textInputFocus:      textInput.focus

    property alias textInputWidth:      textField.implicitWidth
    property alias textInputHeight:     textField.implicitHeight
    property alias textInputBorder:     textField.border
    property alias textInputRadius:     textField.radius

    property color backTextInputColor: "white"
    color: "transparent"

    property var near   //  Объект-сосед, который относится к тексту

    property var textInputObject: textInput === undefined ? undefined : textInput

    signal userChangedFocus(bool focus)
    signal textInputChanged()

    signal acceptText(string text)

    signal selectAll()

    onSelectAll: textInput.selectAll()


    LabelStd
    {
        id: labelStd

        anchors.left: parent.left
        anchors.leftMargin: 0

        anchors.top:            direction === "H" ? undefined : parent.top
        anchors.topMargin: 0

        anchors.verticalCenter: direction === "H" ? parent.verticalCenter : undefined
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.ArrowCursor
            onClicked: selectAll()
        }
    }

    Rectangle {
        id: textField
        color: backTextInputColor
        implicitHeight: 26
        implicitWidth: 60

        anchors.left:           direction === "H" ? labelStd.right : parent.left
        anchors.leftMargin:     direction === "H" ? 4 : 0

        anchors.top:            direction === "H" ? undefined : labelStd.bottom
        anchors.topMargin:      direction === "H" ? 0 : 4

        anchors.verticalCenter: direction === "H" ? parent.verticalCenter : undefined

        TextInput {
            id: textInput
            verticalAlignment: TextEdit.AlignVCenter
            anchors.fill:parent
            anchors.margins: 4
            selectByMouse: true
            clip: true

            onTextChanged: textInputStd.textInputChanged()


            onAccepted: acceptText(currentTextInput)

            onFocusChanged: {
                textInputStd.userChangedFocus(focus)
                if (focus) cursorPosition = 0
                else textInput.deselect()
            }
        }
    }

    function setAlignment(args) {
        var countAlignment
        if (Array.isArray(args))
            countAlignment= args.length
        else if (args === undefined) countAlignment = 0
        else countAlignment = 1
        var alignments = []
        if (countAlignment === 1) alignments[0] = args
        else alignments = args

        for(var j = 0; j < countAlignment; j++ ) {
            switch (alignments[j]) {
            case Qt.AlignBottom:
                textInput.anchors.bottom = textInput.parent.bottom
                break;

            case Qt.AlignTop:
                textInput.anchors.top = textInput.parent.top
                break;

            case Qt.AlignRight:
                textInput.anchors.right = textInput.parent.right
                break

            case Qt.AlignLeft:
                textInput.anchors.left = textInput.parent.left
                break

            case Qt.AlignHCenter:
                textInput.anchors.horizontalCenter = textInput.parent.horizontalCenter
                break

            case Qt.AlignVCenterv:
                textInput.anchors.verticalCenter = textInput.parent.verticalCenter
                break
            }

        }
    }

    states: [
        State{
            name: "nonPressed"
            when: !enabled
            PropertyChanges {
                target: textInputStd
                opacity: 0.5
            }
        }
    ]

    Behavior on opacity {
        NumberAnimation {
            duration: textInputStd.durationAnimation
        }
    }
}

