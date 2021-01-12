#include "..\include\backfrontbridge.h"
#include "..\forDebug\loggingCategories.h"

//BackFrontBridge - Мост между Back и Front - мост для соединения между GUI и Backend
BackFrontBridge::BackFrontBridge(QObject *parent) : QObject(parent)
{
}

//connected() - Вернуть статус подключения.
quint8 BackFrontBridge::connected() const
{
    return m_connected;
}

//command() - Вернуть текущую установленную комманду
QString BackFrontBridge::command() const
{
    return m_command;
}

//telemetry() - Вернуть карту телеметрии
QVariantMap BackFrontBridge::telemetry() const
{
    return m_telemetry;
}

//errorString() - Вернуть строку ошибки
QString BackFrontBridge::errorString() const
{
    return m_errorString;
}

//halfSetOpMode() - Вернуть карту вышедших на рабочий режим полукоплектов
QVariantMap BackFrontBridge::halfSetOpMode() const
{
    return m_halfSetOpMode;
}

//setConnected() - Установить статус подключения (здесь из Backend)
void BackFrontBridge::setConnected(quint8 connected)
{
    if (m_connected == connected)
        return;

    m_connected = connected;
    emit connectedChanged(m_connected);
}

//setCommand() - Установить новую комманду (здесь из GUI)
void BackFrontBridge::setCommand(QString command)
{
    if (m_command == command)
        return;

    m_command = command;
    emit commandChanged(m_command);
}

//setTelemetry() - Установить карту телеметрии (здесь из Backend)
void BackFrontBridge::setTelemetry(QVariantMap telemetry)
{
    if (m_telemetry == telemetry)
        return;

    m_telemetry = telemetry;
    emit telemetryChanged(m_telemetry);
}

//setErrorString() - Установить строку ошибки (здесь из Backend)
void BackFrontBridge::setErrorString(QString errorString)
{
    if (m_errorString == errorString)
        return;

    m_errorString = errorString;
    emit errorStringChanged(m_errorString);
}

//setHalfSetOpMode() - Установить карту вышедших на рабочий режим полукоплектов (здесьиз Backend)
void BackFrontBridge::setHalfSetOpMode(QVariantMap halfSetOpMode)
{
    if (m_halfSetOpMode == halfSetOpMode)
        return;

    m_halfSetOpMode = halfSetOpMode;
    emit halfSetOpModeChanged(m_halfSetOpMode);
}
