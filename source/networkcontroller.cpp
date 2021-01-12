#include "..\include\networkcontroller.h"
#include "..\forDebug\loggingcategories.h"

#include <QDir>
#include <QNetworkConfigurationManager>
#include <QSettings>


//  NetworkController - Контроллер Сети - управляет подключением по сети, настраивает сеть.
NetworkController::NetworkController(QObject *parent) : QObject(parent)
{
    //  Создание дирректорию с файлом конфигурации, если она отсутствует.
    QDir dataDir;
    dataDir.mkdir(m_configDir);
}

//  initAndStart() - Инициализация и старт. Контроллер пытается подключиться к сети.
void NetworkController::initAndStart()
{
    //  Попытка подключения.
    tryConnect();
}

//   connectedState() - Вернуть значение состояния сети.
quint8 NetworkController::connectedState() const
{
    return m_connectedState;
}

//  setHostConfiguration() - Установить конфигурации хоста из файла Protocol::_CONFIG_NET_FILE_NAME.
void NetworkController::setHostConfiguration()
{
    setErrorCode(RC::ErrorCode::NotError);

    QFile configFile(m_configFileName);
    if (!configFile.open(QIODevice::ReadOnly)){
        setErrorCode(RC::ErrorCode::WrongConfig);
    }
    else{
        QString tmp = QString::fromUtf8(configFile.readAll());
        QStringList splitStrings;
        splitStrings = tmp.split("\r\n");

        QStringList values;
        for (QString string: splitStrings)
            values.append(string.split(":"));

        m_IP = (QHostAddress)values.at(1);
        qInfo(logInfo()) << "IP RP:  \t" << m_IP;

        tmp = values.at(3);
        m_port = tmp.toInt();
        qInfo(logInfo()) << "Порт: \t" << m_port;
    }

}

//  connecting() - Подключение к сети, настройка.
void NetworkController::connecting()
{
    mp_tcpSocket = new QTcpSocket(this);
    connect(mp_tcpSocket, &QIODevice::readyRead, this, &NetworkController::readData);
    connect(mp_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &NetworkController::setNetError);

    connect(mp_tcpSocket, &QTcpSocket::disconnected, this, &NetworkController::setNewConnectedState);
    connect(mp_tcpSocket, &QTcpSocket::connected, this, &NetworkController::setNewConnectedState);

    QNetworkConfigurationManager manager;   //  Менеджер конфигурации сети.

    //   Далее описываются действия, которые будут выполнены,
    //  если система требует установки сетевой сессии перед выполнением сетевых операций.
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        //   Получение сетевых настроек.
        QSettings settings(QSettings::UserScope, QLatin1String("TCP_setting"));
        settings.beginGroup("Network");
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        //   Если не обнаружено сохраненных сетевых настроек по умолчанию, то используется дефолтная сетевая конфигурация.
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
        {
            config = manager.defaultConfiguration();
        }

        //   Работа с сетевой сессией.
        mp_networkSession = new QNetworkSession (config, this);    //  Сетевая сессия.

        //   Соединение сигнал об открытии новой сессии со слотом sessionOpened,
        // который задает конфигурацию сети.
        connect(mp_networkSession, &QNetworkSession::opened, this, &NetworkController::sessionOpened);

        //   Открытие сетевой сессии.
        mp_networkSession -> open();
    }
    mp_tcpSocket->connectToHost(m_IP, m_port);

}

//  errorCode() - Вернуть значение кода ошибки errorCode.
RC::ErrorCode NetworkController::errorCode()
{
    return m_errorCode;
}

//  setNoNetError() - Очистить ошибку netErrorCode.
void NetworkController::setNoNetError()
{
    if (errorCode() == RC::ErrorCode::NetError)
        setErrorCode(RC::ErrorCode::NotError);
    delete mp_netError;
    mp_netError = nullptr;
}

//  sendData(QByteArray) - Отправить данные в сокет.
void NetworkController::sendData(QByteArray data)
{
    m_sendDataFlag = RC::_FALSE;
    if (mp_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        qInfo(logInfo()) << "Send command:\t" << data;
        m_sendDataFlag = RC::_TRUE;
        mp_tcpSocket ->write(data);
        mp_tcpSocket->readyRead();
    }
}

//  tryConnect() - Попытаться подключиться к сети (в нее входит установка конфигурации хоста).
void NetworkController::tryConnect()
{
    //  Установка конфигурации хоста из файла.
    setHostConfiguration();
    if (errorCode() == RC::ErrorCode::WrongConfig)
        return;
    else
        connecting();
}

// setConnectedState(quint8) - Установить текущее состояние сети. Если состояние Connected то RC::_TRUE, иначе RC::_FALSE.
void NetworkController::setConnectedState(quint8 connectedState)
{
    if (m_connectedState == connectedState)
        return;

    m_connectedState = connectedState;
    emit connectedStateChanged(m_connectedState);
}


//  sessionOpened() - Действия после открытия сессии. Задание конфигурации сети при получении сегнала об открытии новой сетевой сессии.
void NetworkController::sessionOpened()
{
    //   Сохранение используемой конфигурации.
    QNetworkConfiguration config = mp_networkSession->configuration();

    QString id;

    if (config.type() == QNetworkConfiguration::UserChoice)
        id = mp_networkSession -> sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = m_IP.toString() + "_" + QStringLiteral("%1").arg(m_port);

    //   Установка сетевых настроек по умолчанию.
    QSettings settings (QSettings::UserScope, QLatin1String("TCP_setting"));
    settings.beginGroup(QLatin1String("Network"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}


//  readData() - Чтение данных из сокета.
void NetworkController::readData()
{
    if (!m_sendDataFlag){
        QByteArray data;
        data = mp_tcpSocket->readAll();
        emit dataReceived(data);
    }
    else m_sendDataFlag = RC::_FALSE;
}

//  setNetError() - Установить ошибку сети.
void NetworkController::setNetError(QAbstractSocket::SocketError socketError)
{
    setErrorCode(RC::ErrorCode::NetError);

    if (mp_netError == nullptr)
        mp_netError = new QAbstractSocket::SocketError(socketError);
    else
        *mp_netError = QAbstractSocket::SocketError(socketError);
    setNewConnectedState();

}

//  setNewConnectedState() - Установить новое состояние сети. Если произошло подключение по сети,
// то сonnectedState = RC::_TRUE. При любых изменениях статуса подключения сonnectedState = RC::_FALSE.
void NetworkController::setNewConnectedState()
{
    if (mp_tcpSocket->state() == QAbstractSocket::ConnectedState)
        setConnectedState(RC::_TRUE);
    else
        setConnectedState(RC::_FALSE);
}

//  setNetError() - Установить код ошибки errorCode.
void NetworkController::setErrorCode(const RC::ErrorCode &errorCode)
{
    if (m_errorCode == errorCode)
        return;

    m_errorCode = errorCode;
    emit errorCodeChanged(errorCode);
}
