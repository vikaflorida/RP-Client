import QtQuick 2.9
import QtQml 2.2
import QtQuick.Controls 1.4 as QQC1
import QtQuick.Controls 2.2 as QQC2
import QtQuick.Controls.Styles 1.4

QQC1.TextArea {
    id: textArea
    property string toolTipText: textArea.text
    property bool toolTipTextVisible: true
    width: 64
    height: 44
    readOnly: true
    readonly property int stdHeight: Qt.application.font.pixelSize * 2
    verticalAlignment: TextEdit.AlignVCenter
    style: TextAreaStyle {
        backgroundColor:"#505050"
        textColor: "#f0f0f0"
        selectedTextColor: "#505050"
        selectionColor: "#f0f0f0"
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    QQC2.ToolTip {
        visible: ((textArea.toolTipTextVisible) && (mouseArea.containsMouse))
        text: toolTipText
        delay: 1000
        timeout: 5000
    }
}
