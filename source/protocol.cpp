#include "../include/protocol.h"

QVariant Protocol::FormatFirstSizeType::toQVariant()
{
    QList<QVariant> list;
    list.append(format);
    list.append(first);
    list.append(size);
    list.append(type);
    QVariant tmp(list);
    return tmp;
}


//№№№ Protocol::TelemetryProtocol - содержит протокол телеметрии.
// Если какие-либо биты, байты неустановлены, то они должны быть обнулены.
Protocol::TelemetryProtocol::TelemetryProtocol()
{
    // FormatFirstSizeType
    // Format -  в массиве сырых данных в данном поле байты или биты.
    // First -  индекс первого байта (бита) начиная с 0 (0 - начало массива сырых данных).
    // Size -  количество байт (бит) в данном поле.
    // Type -  тип данных в поле.
    m_telemetryProtocol[_Identif]      =   FormatFirstSizeType(Byte, 0, 1, Int);

    m_telemetryProtocol[_KIT_2_1_ON]          =   FormatFirstSizeType(Bit, 11, 1, Bool);
    m_telemetryProtocol[_KIT_2_2_ON]          =   FormatFirstSizeType(Bit, 12, 1, Bool);
    m_telemetryProtocol[_KIT_1_1_ON]          =   FormatFirstSizeType(Bit, 13, 1, Bool);
    m_telemetryProtocol[_KIT_1_2_ON]          =   FormatFirstSizeType(Bit, 14, 1, Bool);
    m_telemetryProtocol[_KIT_V]          =   FormatFirstSizeType(Bit, 15, 1, Bool);

    m_telemetryProtocol[_Last_Command]     =   FormatFirstSizeType(Byte, _COMMAND_FIRST_BYTE, _COMMAND_BYTE_COUNT, StringInByteArray);

    m_telemetryProtocol[_Temperature_KIT_2 + "1"]  =   FormatFirstSizeType(Byte, 12, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_2 + "2"]  =   FormatFirstSizeType(Byte, 14, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_2 + "3"]  =   FormatFirstSizeType(Byte, 16, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_2 + "4"]  =   FormatFirstSizeType(Byte, 18, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_2 + "5"]  =   FormatFirstSizeType(Byte, 20, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_2 + "6"]  =   FormatFirstSizeType(Byte, 22, 2, Real_7e4);

    m_telemetryProtocol[_Temperature_KIT_1 + "1"]  =   FormatFirstSizeType(Byte, 24, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_1 + "2"]  =   FormatFirstSizeType(Byte, 26, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_1 + "3"]  =   FormatFirstSizeType(Byte, 28, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_1 + "4"]  =   FormatFirstSizeType(Byte, 30, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_1 + "5"]  =   FormatFirstSizeType(Byte, 32, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_1 + "6"]  =   FormatFirstSizeType(Byte, 34, 2, Real_7e4);

    m_telemetryProtocol[_Temperature_KIT_3 +"2"]  =   FormatFirstSizeType(Byte, 36, 2, Real_7e4);
    m_telemetryProtocol[_Temperature_KIT_3 +"3"]  =   FormatFirstSizeType(Byte, 38, 2, Real_7e4);

    m_telemetryProtocol[_Temperature_C] =   FormatFirstSizeType(Byte, 40, 2, Real_7e4);

    m_telemetryProtocol[_Current_V]     =   FormatFirstSizeType(Byte, 42, 2, Real_7e4);

    m_telemetryProtocol[_Current_KIT_2 + "1"]    =   FormatFirstSizeType(Byte, 44, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_2 + "2"]    =   FormatFirstSizeType(Byte, 46, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_2 + "3"]    =   FormatFirstSizeType(Byte, 48, 2, Real_7e4);

    m_telemetryProtocol[_Current_KIT_2 + "4"]    =   FormatFirstSizeType(Byte, 50, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_2 + "5"]    =   FormatFirstSizeType(Byte, 52, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_2 + "6"]    =   FormatFirstSizeType(Byte, 54, 2, Real_7e4);

    m_telemetryProtocol[_Current_KIT_1 + "1"]    =   FormatFirstSizeType(Byte, 56, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_1 + "2"]    =   FormatFirstSizeType(Byte, 58, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_1 + "3"]    =   FormatFirstSizeType(Byte, 60, 2, Real_7e4);

    m_telemetryProtocol[_Current_KIT_1 + "4"]    =   FormatFirstSizeType(Byte, 62, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_1 + "5"]    =   FormatFirstSizeType(Byte, 64, 2, Real_7e4);
    m_telemetryProtocol[_Current_KIT_1 + "6"]    =   FormatFirstSizeType(Byte, 66, 2, Real_7e4);

    m_telemetryProtocol[_Code_Error_TELEM]  =   FormatFirstSizeType(Byte, 68, 2, Int);

    m_telemetryProtocol[_Hourse_TIME]        =   FormatFirstSizeType(Byte, 12, 2, Int);
    m_telemetryProtocol[_Minutes_TIME]       =   FormatFirstSizeType(Byte, 14, 2, Int);
    m_telemetryProtocol[_Code_Error_TIME]    =   FormatFirstSizeType(Byte, 16, 2, Int);
}

QMap<QString, Protocol::FormatFirstSizeType> Protocol::TelemetryProtocol::telemetryProtocol()
{
    return m_telemetryProtocol;
}

QMap<QString, QVariant> Protocol::TelemetryProtocol::telemetryProtocol_Q()
{
    QMap<QString, QVariant> telemetryProtocol_q;
    QMap<QString, FormatFirstSizeType>::const_iterator telemetryIterator = m_telemetryProtocol.constBegin();
    while (telemetryIterator != m_telemetryProtocol.constEnd())
    {
        telemetryProtocol_q[telemetryIterator.key()] = m_telemetryProtocol[telemetryIterator.key()].toQVariant();
        telemetryIterator++;
    }
    return telemetryProtocol_q;
}

// Protocol::CommandProtocol - содержит протокол комманд.
Protocol::CommandProtocol::CommandProtocol()
{
    m_commandProtocol[_KIT_1_1_ON_COM]        = _KIT_1_1_IS_ON;
    m_commandProtocol[_KIT_1_1_OFF_COM]       = _KIT_1_1_IS_OFF;
    m_commandProtocol[_KIT_1_2_ON_COM]        = _KIT_1_2_IS_ON;
    m_commandProtocol[_KIT_1_2_OFF_COM]       = _KIT_1_2_IS_OFF;
    m_commandProtocol[_KIT_2_1_ON_COM]        = _KIT_2_1_IS_ON;
    m_commandProtocol[_KIT_2_1_OFF_COM]       = _KIT_2_1_IS_OFF;
    m_commandProtocol[_KIT_2_2_ON_COM]        = _KIT_2_2_IS_ON;
    m_commandProtocol[_KIT_2_2_OFF_COM]       = _KIT_2_2_IS_OFF;
    m_commandProtocol[_KIT_1_KIT_2_OFF]        = _ALL_OFF;
    m_commandProtocol[_Request_TELEM]          = _IS_TELEM;
    m_commandProtocol[_Request_TIME]           = _IS_TIME;
}

QVariantMap Protocol::CommandProtocol::commandProtocol()
{
    return m_commandProtocol;
}
