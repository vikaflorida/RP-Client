#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>
#include <QThread>
#include "backfrontbridge.h"
#include "telemetryhandler.h"
#include "networkcontroller.h"
#include "operatingmodecontroller.h"
#include "runningtimecontoller.h"
#include "rc.h"

//№№№  Backend - осуществляет взаимодействие между сетью, командами и GUI.
class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(RC::ErrorCode errorCode READ errorCode WRITE setErrorCode NOTIFY errorCodeChanged)

public:
private:
    QByteArray m_rawData;
    QVariantMap m_telemetry;
    RC::Command m_commandBase;
    BackFrontBridge *mp_backFrontBridge = nullptr;
    NetworkController *mp_networkController = nullptr;
    OperatingModeController m_operatingModeController;
    QThread *mp_opModeThread = nullptr;
    RunningTimeContoller m_runningTimeController;
    TelemetryHandler m_telemetryHandler;
    QByteArray m_command;
    QTimer m_timerTelemetry;
    RC::ErrorCode m_errorCode = RC::ErrorCode::NetworkInitError;

public:
    explicit Backend(QObject *parent);
    explicit Backend(NetworkController &networkController, QObject *parent);
    void setNetworkController(NetworkController &networkController);
    BackFrontBridge& getBackFrontBridge();
    void initAndStart();
    QByteArray command() const;
    RC::ErrorCode errorCode() const;

private:
    void addErrorCode(RC::ErrorCode addErrorCode);
    void removeErrorCode(RC::ErrorCode rmErrorCode);
    quint8 errorCodeIncludes(RC::ErrorCode inclErrorCode);
    void requestTelemetry();

public slots:
    void handleTelematry(QByteArray rawData); // Соединяется в main со слотом NetworkController
    void handleErrorCode(RC::ErrorCode errorCode);
    void setCommand(QByteArray command);

private slots:
    void updateTelemetry();
    void requestRunningTime();
    void newCommandCode(QString commandName);
    void handleConnectedState(quint8 connectedState);
    void showError();
    void setErrorCode(const RC::ErrorCode errorCode);
    void setNewTelemetry(QVariantMap telemetry);

signals:
    void newErrorString(QString errorString);
    void commandChanged(QByteArray command);    // Соединяется в main со слотом NetworkController
    void errorCodeChanged(RC::ErrorCode errorCode);
};


#endif // BACKEND_H
