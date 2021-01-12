#ifndef OPERATINGMODECONTROLLER_H
#define OPERATINGMODECONTROLLER_H

#include <QObject>
#include "rc.h"
#include "protocol.h"

// OperatingModeController - Контроллер Рабочего Режима
class OperatingModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RC::ErrorCode errorCode READ errorCode WRITE setErrorCode NOTIFY errorCodeChanged)

private:
    QString m_configDir = Protocol::_CONFIG_DIR;
    QString m_configFileName = Protocol::_CONFIG_OP_MODE_FILE_NAME;
    qreal m_temperature = 0.0;
    qreal m_tolerance = 0.0;
    RC::Telemetry m_telemetry;

    std::vector<QVariant> m_opModeSource;
    std::vector<QVariant> m_overOpModeSource;
    QVariantMap m_opModeHalfSet;
    RC::ErrorCode m_errorCode = RC::ErrorCode::ConfigInitError;

public:
    explicit OperatingModeController(QObject *parent = nullptr);
    void initAndStart();
    void checkOperatingMode(QVariantMap telemetry);
    QVariantMap opModeHalfSet() const;
    RC::ErrorCode errorCode() const;


private:
    void setConfiguration();
    void setTemperatureOperatingMode(QString temperature);
    void setToleranceOperatingMode(QString tolerance);
    void detectOperatingModeHalfSets();
    void addErrorCode(RC::ErrorCode addErrorCode);
    void removeErrorCode(RC::ErrorCode rmErrorCode);
    quint8 errorCodeIncludes(RC::ErrorCode inclErrorCode);

public slots:
private slots:
    void showError();
    void setErrorCode(const RC::ErrorCode errorCode);

signals:
    void errorCodeChanged(RC::ErrorCode errorCode);
    void newOperatingModeHalfSets(QVariantMap opModeHalfSet);

};

#endif // OPERATINGMODECONTROLLER_H
