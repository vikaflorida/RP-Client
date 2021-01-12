#ifndef TELEMETRYHANDLER_H
#define TELEMETRYHANDLER_H
#include "protocol.h"
#include "rc.h"
#include <QObject>
#include <QVariantMap>


//   TelemetryHandler - обработчик тедеметрических данных.
class TelemetryHandler : public QObject
{
    Q_OBJECT

public:
private:
    QByteArray m_rawData;
    std::vector<QByteArray> m_rawDataSet;

    RC::Telemetry m_telemetry;
    Protocol::TelemetryProtocol m_telemetryProtocol;
    Protocol::CommandProtocol m_commandProtocol;

public:
    explicit TelemetryHandler(QObject *parent = nullptr);
    explicit TelemetryHandler(QByteArray rawData, QObject *parent = nullptr);
    void parseTelemetry();
    void setRawData(const QByteArray &rawData);

private:
    void checkCountTelemtry();
    void findTelemetryInRawData();
    QString convertTelemtryCode(QString telemetryName);
    QByteArray getBitArray(quint32 first, quint32 size);
    QByteArray getByteArray(quint32 first, quint32 size);
    void removeWasteTelemetry(QVariantMap &telemetry);

public slots:

private slots:

signals:
    newTelemetry(QVariantMap telemetry);
};

#endif // TELEMETRYHANDLER_H
