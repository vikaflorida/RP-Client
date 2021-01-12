import QtQuick 2.0
import QtQuick.Layouts 1.3
import "./elementStd" as ESTD
import "./elementSpec" as ESPEC
import "appcolors.js" as Colors

//  Элемент отображения телеметрии
Item {
    id: tele

    property var telemetry                 //  Телеметрия (QVariant)
    property bool show: false              //  Флаг отображения элемента
    onTelemetryChanged: {
        for (var prop in telemetry)
        {
            if (prop.indexOf("Temperature") >= 0)
            {
                if (prop.indexOf("Kit11") >= 0) tele.setText(t_KIT1_1, telemetry[prop])
                else if (prop.indexOf("Kit12") >= 0) tele.setText(t_KIT1_2, telemetry[prop])
                else if (prop.indexOf("Kit13") >= 0) tele.setText(t_KIT1_3, telemetry[prop])
                else if (prop.indexOf("Kit14") >= 0) tele.setText(t_KIT1_4, telemetry[prop])
                else if (prop.indexOf("Kit15") >= 0) tele.setText(t_KIT1_5, telemetry[prop])
                else if (prop.indexOf("Kit16") >= 0) tele.setText(t_KIT1_6, telemetry[prop])

                else if (prop.indexOf("Kit21") >= 0) tele.setText(t_KIT2_1, telemetry[prop])
                else if (prop.indexOf("Kit22") >= 0) tele.setText(t_KIT2_2, telemetry[prop])
                else if (prop.indexOf("Kit23") >= 0) tele.setText(t_KIT2_3, telemetry[prop])
                else if (prop.indexOf("Kit24") >= 0) tele.setText(t_KIT2_4, telemetry[prop])
                else if (prop.indexOf("Kit25") >= 0) tele.setText(t_KIT2_5, telemetry[prop])
                else if (prop.indexOf("Kit26") >= 0) tele.setText(t_KIT2_6, telemetry[prop])

                else if (prop.indexOf("Kit31") >= 0) tele.setText(t_KIT_3_1, telemetry[prop])
                else if (prop.indexOf("Kit32") >= 0) tele.setText(t_KIT_3_2, telemetry[prop])
                else if (prop.indexOf("KitC") >= 0) tele.setText(t_KIT_C, telemetry[prop])
            }
            if (prop.indexOf("Current") >= 0)
            {
                if (prop.indexOf("Kit11") >= 0) tele.setText(cur_KIT_1_1, telemetry[prop])
                if (prop.indexOf("Kit12") >= 0) tele.setText(cur_KIT_1_2, telemetry[prop])
                if (prop.indexOf("Kit13") >= 0) tele.setText(cur_KIT_1_3, telemetry[prop])
                if (prop.indexOf("Kit14") >= 0) tele.setText(cur_KIT_1_4, telemetry[prop])
                if (prop.indexOf("Kit15") >= 0) tele.setText(cur_KIT_1_5, telemetry[prop])
                if (prop.indexOf("Kit16") >= 0) tele.setText(cur_KIT_1_6, telemetry[prop])

                if (prop.indexOf("Kit21") >= 0) tele.setText(cur_KIT_2_1, telemetry[prop])
                if (prop.indexOf("Kit22") >= 0) tele.setText(cur_KIT_2_2, telemetry[prop])
                if (prop.indexOf("Kit23") >= 0) tele.setText(cur_KIT_2_3, telemetry[prop])
                if (prop.indexOf("Kit24") >= 0) tele.setText(cur_KIT_2_4, telemetry[prop])
                if (prop.indexOf("Kit25") >= 0) tele.setText(cur_KIT_2_5, telemetry[prop])
                if (prop.indexOf("Kit26") >= 0) tele.setText(cur_KIT_2_6, telemetry[prop])

                if (prop.indexOf("KitK") >= 0) tele.setText(cur_KIT_V, telemetry[prop])
            }
        }
    }

    ESTD.GridLayoutStd{
        id: grid
        rows: 10
        columns: 3

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT1_1
            location: [grid, 1, 1, 1, 1]
            label.text: "Температура KIT1.1"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT1_2
            location: [grid, 1, 2, 1, 1]
            label.text: "Температура KIT1.2"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT1_3
            location: [grid, 1, 3, 1, 1]
            label.text: "Температура KIT1.3"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT1_4
            location: [grid, 2, 1, 1, 1]
            label.text: "Температура KIT1.4"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT1_5
            location: [grid, 2, 2, 1, 1]
            label.text: "Температура KIT1.5"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT1_6
            location: [grid, 2, 3, 1, 1]
            label.text: "Температура KIT1.6"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT2_1
            location: [grid, 3, 1, 1, 1]
            label.text: "Температура KIT2.1"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT2_2
            location: [grid, 3, 2, 1, 1]
            label.text: "Температура KIT2.2"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT2_3
            location: [grid, 3, 3, 1, 1]
            label.text: "Температура KIT2.3"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT2_4
            location: [grid, 4, 1, 1, 1]
            label.text: "Температура KIT2.4"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT2_5
            location: [grid, 4, 2, 1, 1]
            label.text: "Температура KIT2.5"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT2_6
            location: [grid, 4, 3, 1, 1]
            label.text: "Температура KIT2.5"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT_C
            location: [grid, 5, 1, 1, 1]
            label.text: "Температура KIT K"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT_3_1
            location: [grid, 5, 2, 1, 1]
            label.text: "Температура KIT3.1"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: t_KIT_3_2
            location: [grid, 5, 3, 1, 1]
            label.text: "Температура KIT3.2"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_1_1
            location: [grid, 6, 1, 1, 1]
            label.text: "Ток KIT1.1"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_1_2
            location: [grid, 6, 2, 1, 1]
            label.text: "Ток KIT1.2"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_1_3
            location: [grid, 6, 3, 1, 1]
            label.text: "Ток KIT1.3"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_1_4
            location: [grid, 7, 1, 1, 1]
            label.text: "Ток KIT1.4"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_1_5
            location: [grid, 7, 2, 1, 1]
            label.text: "Ток KIT1.5"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_1_6
            location: [grid, 7, 3, 1, 1]
            label.text: "Ток KIT1.6"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_2_1
            location: [grid, 8, 1, 1, 1]
            label.text: "Ток KIT2.1"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_2_2
            location: [grid, 8, 2, 1, 1]
            label.text: "Ток KIT2.2"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_2_3
            location: [grid, 8, 3, 1, 1]
            label.text: "Ток KIT2.3"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_2_4
            location: [grid, 9, 1, 1, 1]
            label.text: "Ток KIT2.4"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_2_5
            location: [grid, 9, 2, 1, 1]
            label.text: "Ток KIT2.5"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_2_6
            location: [grid, 9, 3, 1, 1]
            label.text: "Ток KIT2.6"
        }

        ESPEC.TextInputToGroupTelemetry{
            id: cur_KIT_V
            location: [grid, 10, 1, 1, 1]
            label.text: "Ток KIT V"
        }
    }

    function setText (obj, text){
        obj.text = text
    }


    states: [
        State{
            name: "nonEnabled"
            when: !enabled && show
            PropertyChanges {
                target: tele
                opacity: 0.5
            }
        },

        State{
            name: "nonShow"
            when: !show
            PropertyChanges {
                target: tele
                opacity: 0.0
            }
        }
    ]
}
