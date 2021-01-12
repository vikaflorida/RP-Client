import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4 as QQE
import QtQuick.Controls 1.4 as QQC1
import QtQuick.Controls 2.2 as QQC2

//  Элемент статуса состояния
 QQE.StatusIndicator {
     id: si
     property color offColor: "#383838"   //  Цвет выключенного элемента статуса состояния
     property color onColor: "yellow"     //  Цвет включенного элемента статуса состояния
     property bool visibleToolTip: true   //  Флаг отображения подсказки
     property string toolTipTextSI: ""    //  Текст подсказки статуса состояния
     property int durationAnimation: 100  //  Длительность анимации
     active: false
     color: active ? onColor : offColor

     MouseArea{
         anchors.fill: parent
         hoverEnabled: true

         ToolTipStd{
             visible: visibleToolTip ? parent.containsMouse : undefined
             text: si.toolTipTextSI
         }
     }

     Behavior on color {
         ColorAnimation {
             duration: durationAnimation
         }
     }
 }
