#ifndef BACKFRONTBRIDGE_H
#define BACKFRONTBRIDGE_H
#include <QObject>
#include <QVariantMap>
#include "rc.h"

//BackFrontBridge - Мост между Back и Front - мост для соединения между GUI и Backend
class BackFrontBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QVariantMap telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
    Q_PROPERTY(QString errorString READ errorString WRITE setErrorString NOTIFY errorStringChanged)
    Q_PROPERTY(QVariantMap halfSetOpMode READ halfSetOpMode WRITE setHalfSetOpMode NOTIFY halfSetOpModeChanged)

public:
private:
    quint8 m_connected = RC::_FALSE;
    QString m_command;
    QVariantMap m_telemetry;
    QString m_errorString;
    QVariantMap m_halfSetOpMode;

public:
    explicit BackFrontBridge(QObject *parent = nullptr);
    quint8 connected() const;
    QString command() const;
    QVariantMap telemetry() const;
    QString errorString() const;
    QVariantMap halfSetOpMode() const;

private:

public slots:
    void setConnected(quint8 connected);
    void setCommand(QString command);
    void setTelemetry(QVariantMap telemetry);
    void setErrorString(QString errorString);
    void setHalfSetOpMode(QVariantMap halfSetOpMode);

private slots:

signals:
    void connectedChanged(quint8 connected);
    void commandChanged(QString command);
    void telemetryChanged(QVariantMap telemetry);
    void tryConnect();
    void errorStringChanged(QString errorString);
    void halfSetOpModeChanged(QVariantMap halfSetOpMode);
};



#endif // BACKFRONTBRIDGE_H
