#include "..\include\telemetryhandler.h"
#include <qmath.h>
#include <QString>

//   TelemetryHandler - обработчик тедеметрических данных.
//      Из сырых данных с помощью parseTelemetry и Protocol::TelemetryProtocol
//  могут быть получена хэш-таблица телеметрии.
TelemetryHandler::TelemetryHandler(QObject *parent) :
    QObject(parent)
{

}

TelemetryHandler::TelemetryHandler(QByteArray rawData, QObject *parent) :
    QObject(parent),
    m_rawData(rawData)
{

}

//   parseTelemetry - преобразовать сырые данные в хэш-таблицу.
void TelemetryHandler::parseTelemetry()
{
    checkCountTelemtry();
    QVariantMap telemetry = m_telemetry.telemetry();
    for (quint32 i =0; i < m_rawDataSet.size(); i++)
    {
        m_rawData = m_rawDataSet.at(i);
        QVariantMap::iterator telemetryIterator = telemetry.begin();
        while (telemetryIterator != telemetry.end())
        {
            telemetry[telemetryIterator.key()] = convertTelemtryCode(telemetryIterator.key());
            telemetryIterator++;
        }
        removeWasteTelemetry(telemetry);
        emit newTelemetry(telemetry);
    }
}

//   removeWasteTelemetry() - удалить лишние поля телметрии для каждой команды.
void TelemetryHandler::removeWasteTelemetry(QVariantMap &telemetry)
{
    if (telemetry[Protocol::_Last_Command].toString().indexOf(Protocol::_TIME) <= 0){
        telemetry.remove(Protocol::_Hourse_TIME);
        telemetry.remove(Protocol::_Minutes_TIME);
        telemetry.remove(Protocol::_Code_Error_TIME);
    }
    else{
        telemetry.remove(Protocol::_Temperature_KIT_2 + "1");
        telemetry.remove(Protocol::_Temperature_KIT_2 + "2");
        telemetry.remove(Protocol::_Temperature_KIT_2 + "3");
        telemetry.remove(Protocol::_Temperature_KIT_2 + "4");
        telemetry.remove(Protocol::_Temperature_KIT_2 + "5");
        telemetry.remove(Protocol::_Temperature_KIT_2 + "6");
        telemetry.remove(Protocol::_Temperature_KIT_1 + "1");
        telemetry.remove(Protocol::_Temperature_KIT_1 + "2");
        telemetry.remove(Protocol::_Temperature_KIT_1 + "3");
        telemetry.remove(Protocol::_Temperature_KIT_1 + "4");
        telemetry.remove(Protocol::_Temperature_KIT_1 + "5");
        telemetry.remove(Protocol::_Temperature_KIT_1 + "6");
        telemetry.remove(Protocol::_Temperature_KIT_3 + "2");
        telemetry.remove(Protocol::_Temperature_KIT_3 + "3");
        telemetry.remove(Protocol::_Temperature_C);
        telemetry.remove(Protocol::_Current_V);
        telemetry.remove(Protocol::_Current_KIT_2 + "1_4");
        telemetry.remove(Protocol::_Current_KIT_2 + "1_5");
        telemetry.remove(Protocol::_Current_KIT_2 + "1_6");
        telemetry.remove(Protocol::_Current_KIT_2 + "2_4");
        telemetry.remove(Protocol::_Current_KIT_2 + "2_5");
        telemetry.remove(Protocol::_Current_KIT_2 + "2_6");
        telemetry.remove(Protocol::_Current_KIT_1 + "1_4");
        telemetry.remove(Protocol::_Current_KIT_1 + "1_5");
        telemetry.remove(Protocol::_Current_KIT_1 + "1_6");
        telemetry.remove(Protocol::_Current_KIT_1 + "2_4");
        telemetry.remove(Protocol::_Current_KIT_1 + "2_5");
        telemetry.remove(Protocol::_Current_KIT_1 + "2_6");
        telemetry.remove(Protocol::_KIT_2_1_ON);
        telemetry.remove(Protocol::_KIT_2_2_ON);
        telemetry.remove(Protocol::_KIT_1_1_ON);
        telemetry.remove(Protocol::_KIT_V);
        telemetry.remove(Protocol::_KIT_V);
        telemetry.remove(Protocol::_Code_Error_TELEM);
    }
}


//   setRawData() - установить массив сырых данных.
void TelemetryHandler::setRawData(const QByteArray &rawData)
{
    m_rawData = rawData;
}

//   parseTelemetry - проверить количество телеметрии
void TelemetryHandler::checkCountTelemtry()
{
    m_rawDataSet.clear();
    if ((m_rawData.size() == Protocol::_RECEIPT_WITH_TELEM_BYTE_COUNT) ||
            m_rawData.size() == Protocol::_RECEIPT_WITHOUT_TELEM_BYTE_COUNT){
        m_rawDataSet.push_back(m_rawData);
        return;
    }
    else findTelemetryInRawData();
}

//   parseTelemetry - найти телеметрию в сырых данных
void TelemetryHandler::findTelemetryInRawData()
{
    QVariantMap commandMap = m_commandProtocol.commandProtocol();
    QVariantMap indexesMap;
    QVariantMap::iterator commandIterator = commandMap.begin();
    std::vector<qint32> indexesSort;
    while (commandIterator != commandMap.end())
    {
        QString key(commandIterator.key());
        QString command(commandMap[key].toString());
        qint32 indexStart = static_cast<qint32>(m_rawData.indexOf(command));
        if (indexStart < 0){}
        else{
            indexesMap[command] = indexStart;
            indexesSort.push_back(indexStart);
        }
        commandIterator++;
    }
    std::sort(indexesSort.begin(), indexesSort.end());


    QVariantMap::iterator indexesIterator = indexesMap.begin();
    for (quint32 i = 0; i < static_cast<quint32>(indexesSort.size()); i++)
    {
        QString cmd;
        while (indexesIterator != indexesMap.end())
        {
            if (indexesMap[indexesIterator.key()] == indexesSort.at(i)){
                cmd = QString(indexesIterator.key());
                break;
            }
            indexesIterator++;
        }
        qint32 begin = (indexesSort.at(i) + cmd.size()) - static_cast<qint32>(Protocol::_COMMAND_BYTE_COUNT + Protocol::_COMMAND_FIRST_BYTE);
        qint32 end = 0;
        if (cmd.indexOf(Protocol::_TIME) >= 0)
            end = begin + Protocol::_RECEIPT_WITHOUT_TELEM_BYTE_COUNT;
        else
            end = begin + Protocol::_RECEIPT_WITH_TELEM_BYTE_COUNT;

        QByteArray tmp = m_rawData.mid(begin, end);
        m_rawDataSet.push_back(tmp);
    }
}

//   convertTelemtryCode() - в соответствии с протоколом конвертировать значение из сырых данных.
QString TelemetryHandler::convertTelemtryCode(QString telemetryName)
{
    QByteArray payload;
    QString payloadStr = "";
    Protocol::FormatFirstSizeType ffst =  m_telemetryProtocol.telemetryProtocol()[telemetryName];


    // Выделить массив данных из телеметрии в соответсвии с протоколом
    if (ffst.format == Protocol::Format::Bit)
        payload = getBitArray(ffst.first, ffst.size);

    else if (ffst.format == Protocol::Format::Byte)
        payload = getByteArray(ffst.first, ffst.size);

    switch (ffst.type) {
    case Protocol::Type::Int:
         payloadStr =   QStringLiteral("%1").arg(payload.toHex().toInt(nullptr, 16));
        break;
    case Protocol::Type::Bool:
        if (payload.toHex().toInt(nullptr, 16) == 0)
            payloadStr = "false";
        else
            payloadStr = "true";
        break;
    case Protocol::Type::StringInByteArray:{
        quint32 i = 0;
        while (i < static_cast<quint32>(payload.size()))
        {
            if (payload.at(i) == char(0x0))
                payload.remove(i,1);
            else i++;
        }
        payloadStr = QString(payload);
        break;
    }
    case Protocol::Type::Real_7e4:{
        quint8 tmp1 = static_cast<quint8>(payload.at(0));
        quint8 tmp2 = static_cast<quint8>(payload.at(1));
        payloadStr.append(QStringLiteral("%1.%2").arg(tmp1).arg(tmp2));
        break;
    }
    default:
        break;
    }
    return payloadStr;
}

//   getBitArray() - конвертировать битовое значение из сырых данных.
QByteArray TelemetryHandler::getBitArray(quint32 first, quint32 size)
{
    quint32 passByteCount = static_cast<quint32>(qFloor(static_cast<qreal>(first) / RC::_BYTE_SIZE));
    quint32 passFrontBitCount = first - passByteCount * RC::_BYTE_SIZE;

    quint32 readByteCount = static_cast<quint32>(qCeil(static_cast<qreal>(size)/ RC::_BYTE_SIZE));
    quint32 passBackBitCount = (passByteCount + readByteCount) * RC::_BYTE_SIZE - first - size;
    QByteArray payload;


    for (quint32 i = 0; i < readByteCount; i++)
    {
        payload.append(m_rawData[passByteCount + i]);
    }

    for (quint32 i = readByteCount; i > 0; i--)
    {
        char tmp = payload.at(i - 1);
        tmp = tmp >> passBackBitCount;
        payload[i-1] =  tmp;
    }
    // нулевая маска на первые биты, которые надо пропустить (стоит учитывать, что произошло смещение вправо)
    for (quint32 i = 0; i < (passFrontBitCount + passBackBitCount); i++)
    {
        payload[0] = payload[0] & (~(1 << (RC::_BYTE_SIZE - 1 - i)));
    }
    return payload;
}

//   getBitArray - конвертировать байтовое значение из сырых данных.
QByteArray TelemetryHandler::getByteArray(quint32 first, quint32 size)
{
    QByteArray payload;
    for (quint32 i = 0; i < size; i++)
    {
        payload.append(m_rawData[first + i]);
    }
    return payload;
}
