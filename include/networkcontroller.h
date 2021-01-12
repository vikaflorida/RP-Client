#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QNetworkSession>
#include "rc.h"
#include "protocol.h"

//  NetworkController - Контроллер Сети - управляет подключением по сети, настраивает сеть.
class NetworkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 connectedState READ connectedState WRITE setConnectedState NOTIFY connectedStateChanged)
    Q_PROPERTY(RC::ErrorCode errorCode READ errorCode WRITE setErrorCode NOTIFY errorCodeChanged)

public:
private:
    RC::ErrorCode m_errorCode = RC::ErrorCode::NotError;
    QAbstractSocket::SocketError *mp_netError = nullptr;

    QString m_configDir = Protocol::_CONFIG_DIR;
    QString m_configFileName = Protocol::_CONFIG_NET_FILE_NAME;

    QHostAddress m_IP = (QHostAddress)"";
    quint32 m_port = 0;
    QNetworkSession *mp_networkSession = nullptr;
    QTcpSocket *mp_tcpSocket = nullptr;

    quint8 m_sendDataFlag = RC::_FALSE; // флаг отправки данных (для тго чтобы предотвращать чтение из сокета, если данные в него записаны клиентом)

    quint8 m_connectedState = RC::_FALSE;

public:
    explicit NetworkController(QObject *parent = nullptr);
    void initAndStart();
    quint8 connectedState() const;

private:
    void setHostConfiguration();
    void connecting();
    RC::ErrorCode errorCode();
    void setNoNetError();

public slots:
    void sendData(QByteArray data);
    void tryConnect();
    void setConnectedState(quint8 connectedState);

private slots:
    void sessionOpened();
    void readData();
    void setNetError(QAbstractSocket::SocketError socketError);
    void setNewConnectedState();
    void setErrorCode(const RC::ErrorCode &errorCode);

signals:
    dataReceived(QByteArray data);
    void connectedStateChanged(quint8 connectedState);
    void errorCodeChanged(RC::ErrorCode errorCode);

};

#endif // NETWORKCONTROLLER_H
