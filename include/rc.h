#ifndef RC_H
#define RC_H
#include <QObject>
#include <QVariantMap>

namespace RC {

static const quint8 _FALSE  = 0;
static const quint8 _TRUE   = 1;

static const quint32 _BYTE_SIZE = 8;
static const quint64 _RUNNING_TIME_REQUEST_PERIOD = (1000*60*5);
static const quint64 _TELEMETRY_TIME_REQUEST_PERIOD = (2000);

enum ErrorCode {
    NotError = 0x0000,
    WrongConfig = 0x0001,
    NetError = 0x0002,

    BoardControllerError = 0x0004,

    NetworkControllerError = 0x0008,
    BoardNetworkError = BoardControllerError | NetworkControllerError,

    RunningTimeError = 0x0010,
    BoardRunningError = BoardControllerError | RunningTimeError,
    NetworkRunningError = NetworkControllerError | RunningTimeError,
    BoardNetworkRunningError = BoardNetworkError | RunningTimeError,

    NotInit = 0x0020,
    BoardInitError = BoardControllerError | NotInit,
    NetworkInitError = NetworkControllerError | NotInit,
    RunningInitError = RunningTimeError | NotInit,

    BoardNetworkInitError = BoardNetworkError | NotInit,
    BoardRunningInitError = BoardRunningError | NotInit,

    NetworkRunningInitError = NetworkRunningError | NotInit,

    BoardNetworkRunningInitError = BoardNetworkRunningError | NotInit,

    ConfigInitError = WrongConfig | NotInit
};

class Telemetry{
    QVariantMap m_telemetry;
public:
    Telemetry();
    QVariantMap telemetry() const;
    void setValue(QString key, QString value);
    QPair<QString, QString> telemetryPair(QString name);
};

class Command{
    QVariantMap m_command;
public:
    Command();
    QVariantMap command() const;
    QPair<QString, QByteArray> commandPair(QString name);
};

}



#endif // RC_H
