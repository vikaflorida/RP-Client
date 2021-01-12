#include "../include/rc.h"
#include "../include/protocol.h"


//№№№ RC::Telemetry - содержит работу с контейнером, содержащим хэш таблицу телеметрии.
RC::Telemetry::Telemetry()
{
    Protocol::TelemetryProtocol protocol;
    QVariantMap protocolHash(protocol.telemetryProtocol_Q());
    QVariantMap::const_iterator telemetryIterator = protocolHash.constBegin();
    while (telemetryIterator != protocolHash.constEnd())
    {
        setValue(telemetryIterator.key(), "0");
        telemetryIterator++;
    }
}

QVariantMap RC::Telemetry::telemetry() const
{
    return m_telemetry;
}

void RC::Telemetry::setValue(QString key, QString value)
{
    m_telemetry[key] = value;
}

QPair<QString, QString> RC::Telemetry::telemetryPair(QString name)
{
    return qMakePair(name, m_telemetry[name].toString());
}



//№№№ RC::Telemetry - содержит работу с контейнером, содержащим хэш таблицу команд.
RC::Command::Command()
{
    Protocol::CommandProtocol protocol;
    QVariantMap protocolHash = protocol.commandProtocol();
    QVariantMap::const_iterator telemetryIterator = protocolHash.constBegin();
    while (telemetryIterator != protocolHash.constEnd())
    {
//        m_command[telemetryIterator.key()] = telemetryIterator.value().toString().toUtf8();
        m_command[telemetryIterator.key()] = telemetryIterator.value();
        telemetryIterator++;
    }
}

QVariantMap RC::Command::command() const
{
    return m_command;
}

QPair<QString, QByteArray> RC::Command::commandPair(QString name)
{
    return qMakePair(name, m_command[name].toByteArray());
}
